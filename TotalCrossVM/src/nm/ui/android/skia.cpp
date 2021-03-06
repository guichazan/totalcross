

#include "skia.h"

#if defined darwin
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#if !defined(__arm__) && !defined(ANDROID)
#include <GL/gl.h>
#else
#include <EGL/egl.h>
// #include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#if defined ANDROID
#include <jni.h>
#include <android/bitmap.h>
#endif
#endif
#endif
#if defined HEADLESS
#include "../../../init/tcsdl.h"
#endif
#include <math.h>


#include "SkPathEffect.h"
#include "SkGraphics.h"
#include "SkSurface.h"
#include "SkString.h"
#include "SkTime.h"
#include "SkCanvas.h"
#include "SkRandom.h"
#include "SkTypeface.h"
#include "SkImage.h"
#include "SkImageInfo.h"
#include "SkImageEncoder.h"
#include "SkPath.h"
#include "SkGradientShader.h"

#include "gl/GrGLAssembleInterface.h"
#include "gl/GrGLConfig.h"
#include "gl/GrGLExtensions.h"
#include "gl/GrGLFunctions.h"
#include "gl/GrGLInterface.h"
#include "gl/GrGLTypes.h"

#include "GrBackendSurface.h"
#include "GrContext.h"
#include "GrTypes.h"

#include "SkColorSpace.h"
#include "SkDashPathEffect.h"

#include <vector>
#include <map>


#define SKIA_DEBUG
// #define SKIA_TRACE

#if defined SKIA_DEBUG && defined ANDROID
    #include <android/log.h>
    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "TotalCross", __VA_ARGS__)
#else
    #define LOGD(...) printf("SKIA %s, %d\n", __FUNCTION__, __LINE__)
#endif

#if defined SKIA_TRACE && defined ANDROID
    #define SKIA_TRACE() LOGD(__FUNCTION__);
#else
    #define SKIA_TRACE() //LOGD();
#endif



sk_sp<SkSurface> surface;
SkCanvas *canvas;
SkPaint forePaint; // used for contours
SkPaint backPaint; // used for fills
SkBitmap bitmap;
#define TYPEFACE_LEN 32
sk_sp<SkTypeface> typefaces[TYPEFACE_LEN];
int typefaceIdx = 0;

std::vector<SkBitmap> textures;

std::map<std::string, int> typefaceIndexMap;

void initSkia(int w, int h)
{
    SKIA_TRACE()
#ifdef HEADLESS
    // SkImageInfo ii = SkImageInfo::Make(w, h, kRGB_565_SkColorType, kPremul_SkAlphaType);
    // bitmap.allocPixels(ii, ii.minRowBytes());

        // SkBitmap bitmap;
           bitmap.installPixels(SkImageInfo::Make(w, h, 
           (SkColorType)ColorFormatSDL2Skia(sdlsurface->format->format), kPremul_SkAlphaType), sdlsurface->pixels, sdlsurface->pitch);

    canvas = new SkCanvas(bitmap);
#else
    // To use Skia's GPU backend, a OpenGL context is needed. Skia uses the "Gr" library to abstract
    // the different OpenGL variants (Core, ES, etc). Most of the code bellow is dedicated to create
    // a GL context and produce a valid rendertarget out of it for rendering.
    sk_sp<GrContext> grContext(GrContext::MakeGL(nullptr));

    GLint defaultFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    GrGLFramebufferInfo framebuffer_info;
    framebuffer_info.fFBOID = defaultFBO;
    framebuffer_info.fFormat = GL_RGB8_OES;

    GrBackendRenderTarget render_target(
        w, h, 0, 8,
        framebuffer_info);

    SkSurfaceProps surface_props =
        SkSurfaceProps(0, SkSurfaceProps::kLegacyFontHost_InitType);

    sk_sp<SkSurface> gpuSurface = SkSurface::MakeFromBackendRenderTarget(
        grContext.get(), render_target, kBottomLeft_GrSurfaceOrigin,
        kRGB_888x_SkColorType, nullptr, &surface_props);

    SkCanvas *gpuCanvas = gpuSurface->getCanvas();

    // We cache a reference for the surface and canvas for later use.
    surface = gpuSurface;
    canvas = gpuCanvas;
#endif
    // The forepaint is used for "draw" methods
    forePaint.setStyle(SkPaint::kStroke_Style);
    forePaint.setTextSize(16);
    forePaint.setAntiAlias(true);

    forePaint.setAntiAlias(true);
    forePaint.setLCDRenderText(true);
    // the backpaint is used for "fill" methods
    backPaint.setStyle(SkPaint::kFill_Style);
    backPaint.setTextSize(16);
    backPaint.setAntiAlias(true);

    backPaint.setAntiAlias(true);
    backPaint.setLCDRenderText(true);
    canvas->clear(SK_ColorWHITE);
    flushSkia();
}

// Tells Skia to fullfill all draw commands
void flushSkia()
{
    canvas->flush();
#ifdef HEADLESS
    // updateSDLScreen(bitmap.width(), bitmap.height(), bitmap.getPixels());
    updateSDLScreen(0, 0, NULL);
#endif
}

// Creates a SkTypeface object out of a in-memory TTF file (probably inside some TCZ archive)
int32 skia_makeTypeface(char* name, void *data, int32 size)
{
    SKIA_TRACE()
    std::string key = name;
    int32 idx = skia_getTypefaceIndex(name);
    
    if (idx == -1 && typefaceIdx < TYPEFACE_LEN - 1) {
        sk_sp<SkData> typefaceData = SkData::MakeWithCopy(data, size);
        sk_sp<SkTypeface> typeface = SkTypeface::MakeFromData(typefaceData);
        idx = typefaceIdx;
        typefaces[typefaceIdx++] = typeface;
        typefaceIndexMap[key] = idx;
    }
    
    return idx;
}

int32 skia_getTypefaceIndex(char* name) {
    std::string key = name;
    std::map<std::string, int>::iterator it = typefaceIndexMap.find(key);

    if (it != typefaceIndexMap.end()) {
    	return it->second;
    }
    
    return -1;
}

sk_sp<SkTypeface> skia_getTypeface(int32 typefaceIndex) {
    if (typefaceIndex >= 0 && typefaceIndex < typefaceIdx) {
        return typefaces[typefaceIndex];
    } else {
        return SkTypeface::MakeFromName(nullptr, SkFontStyle());
    }
}

int32 skia_stringWidth(const void *text, int32 charCount, int32 typefaceIndex, int32 fontSize)
{
    backPaint.setTypeface(skia_getTypeface(typefaceIndex));
    backPaint.setTextSize(fontSize);
    return backPaint.measureText(text, charCount);
}

static void releaseProc(void* addr, void* ) {
    // printf("releaseProc called\n");
    delete[] (uint32_t*) addr;
}

int skia_makeBitmap(int32 id, void *data, int32 w, int32 h) {
    SKIA_TRACE()

    //TODO: reuse pixel data and avoid all this allocation, maybe using data directly with the correct color type
    int32 *converted = new int32[w * h];
    for (int i = 0; i < w * h; i++) {
        int32 pixel = ((Pixel*)data)[i];
        converted[i] = (((pixel >> 24) & 0xFF)) | ((((pixel >> 16) & 0xFF) << 8) | (((pixel >> 8) & 0xFF) << 16) | ((pixel & 0xFF) << 24));
    }

    if (id < 0) { // must create a new bitmap
        SkBitmap bitmap;
        bitmap.installPixels(SkImageInfo::Make(w, h, kN32_SkColorType, kUnpremul_SkAlphaType), (void*)converted, sizeof(Pixel) * w, releaseProc, nullptr);
        id = textures.size();
        textures.push_back(bitmap);
    } else {
        SkBitmap& bitmap = textures[id];
        bitmap.installPixels(SkImageInfo::Make(w, h, kN32_SkColorType, kUnpremul_SkAlphaType), (void*)converted, sizeof(Pixel) * w, releaseProc, nullptr);
    }

    return id;
}
void skia_deleteBitmap(int32 id) {
    SKIA_TRACE()

    if (id >= 0) {
        textures[id].reset();
    }
}



void skia_setClip(int32 x1, int32 y1, int32 x2, int32 y2)
{
    canvas->save();
    canvas->clipRect(SkRect::MakeLTRB(x1, y1, x2, y2));
}
void skia_restoreClip()
{
    canvas->restore();
}

void skia_drawSurface(int32 skiaSurface, int32 id, int32 srcX, int32 srcY, int32 srcW, int32 srcH, int32 w, int32 h, int32 dstX, int32 dstY, int32 doClip)
{
    SKIA_TRACE()

    canvas->drawBitmapRect(textures[id], SkRect::MakeXYWH(srcX, srcY, w, h),
                           SkRect::MakeXYWH(dstX, dstY, w, h), nullptr);
}

// The getPixel call demands a 1-pixel readback from the GPU. Avoid it if possible.
Pixel skia_getPixel(int32 skiaSurface, int32 x, int32 y)
{
    SKIA_TRACE()

    SkBitmap bitmap;
    bitmap.allocPixels(SkImageInfo::MakeN32Premul(1, 1));
    if (!canvas->readPixels(bitmap, x, y))
    {
        return -1;
    }

    Pixel pixel = bitmap.getAddr32(0, 0)[0];
    return (((pixel >> 24) & 0xFF) << 24) | (((pixel & 0xFF) << 16) | (((pixel >> 8) & 0xFF) << 8) | ((pixel >> 16) & 0xFF));
}

void skia_setPixel(int32 skiaSurface, int32 x, int32 y, Pixel pixel)
{
    SKIA_TRACE()
    backPaint.setColor(pixel);
    canvas->drawRect(SkRect::MakeXYWH(x, y, 1, 1), backPaint);
}

void skia_drawDottedLine(int32 skiaSurface, int32 x1, int32 y1, int32 x2, int32 y2, Pixel pixel1, Pixel pixel2)
{
    SKIA_TRACE()
    float intervals[] = {5, 5};
    forePaint.setPathEffect(SkDashPathEffect::Make(intervals, 2, 2.5f));
    skia_drawLine(skiaSurface, x1, y1, x2, y2, pixel1);
    forePaint.setPathEffect(nullptr);

    forePaint.setPathEffect(SkDashPathEffect::Make(intervals, 2, 7.5f));
    skia_drawLine(skiaSurface, x1, y1, x2, y2, pixel2);
    forePaint.setPathEffect(nullptr);
}

void skia_drawLine(int32 skiaSurface, int32 x1, int32 y1, int32 x2, int32 y2, Pixel pixel)
{
    SKIA_TRACE()
    forePaint.setColor(pixel);
    canvas->drawLine(x1, y1, x2, y2, forePaint);
}

void skia_drawRect(int32 skiaSurface, int32 x, int32 y, int32 w, int32 h, Pixel pixel)
{
    SKIA_TRACE()
    forePaint.setColor(pixel);
    canvas->drawRect(SkRect::MakeXYWH(x, y, w, h), forePaint);
}

void skia_fillRect(int32 skiaSurface, int32 x, int32 y, int32 w, int32 h, Pixel pixel)
{
    SKIA_TRACE()
    backPaint.setColor(pixel);
    canvas->drawRect(SkRect::MakeXYWH(x, y, w, h), backPaint);
}

void skia_drawText(int32 skiaSurface, const void *text, int32 chrCount, int32 x0, int32 y0, Pixel foreColor, int32 justifyWidth, int32 fontSize, int32 typefaceIndex)
{
    SKIA_TRACE()

    backPaint.setTypeface(skia_getTypeface(typefaceIndex));
    backPaint.setTextEncoding(SkPaint::kUTF16_TextEncoding);
    backPaint.setColor(foreColor);
    backPaint.setTextSize(fontSize);
    canvas->drawText(text, chrCount, x0, y0, backPaint);
}

void skia_ellipseDrawAndFill(int32 skiaSurface, int32 xc, int32 yc, int32 rx, int32 ry, Pixel pc1, Pixel pc2, bool fill, bool gradient)
{
    SKIA_TRACE()
    if (fill) {
        if (gradient) {
            SkPoint points[3] = {
                    SkPoint::Make(xc, yc - ry),
                    SkPoint::Make(xc, yc + ry),
                    SkPoint::Make(xc, yc + ry * 2)
            };
            SkColor colors[3] = {pc2, pc1, pc2};
            backPaint.setShader(SkGradientShader::MakeLinear(
                    points, colors, nullptr, 3,
                    SkShader::kClamp_TileMode, 0, nullptr));
            canvas->drawOval(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), backPaint);
            backPaint.setShader(nullptr);
        } else {
            backPaint.setColor(pc2);
            canvas->drawOval(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), backPaint);
        }
    } else {
        forePaint.setColor(pc1);
        canvas->drawOval(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), forePaint);
    }
}

SkPath _skia_makePath(int32 *x, int32 *y, int32 n)
{
    SKIA_TRACE()
    SkPath path;
    path.moveTo(x[0], y[0]);
    for (int i = 1; i < n; ++i) {
        path.lineTo(x[i], y[i]);
    }

    return path;
}
void _skia_getPathBounds(int32 *x, int32 *y, int32 n, int32* minY, int32* maxY)
{
    SKIA_TRACE()
    *minY = y[0];
    *maxY = y[0];
    for (int i = 1; i < n; ++i) {
        *minY = y[i] < *minY ? y[i] : *minY;
        *maxY = *maxY < y[i] ? y[i] : *maxY;
    }
}
void skia_drawPolygon(int32 skiaSurface, int32 *xPoints, int32 *yPoints, int32 nPoints, int32 tx, int32 ty, Pixel pixel)
{
    SKIA_TRACE()
    forePaint.setColor(pixel);
    canvas->translate(tx, ty);
    canvas->drawPath(_skia_makePath(xPoints, yPoints, nPoints), forePaint);
    canvas->translate(-tx, -ty);
}

void skia_fillPolygon(int32 skiaSurface, int32 *xPoints, int32 *yPoints, int32 nPoints, int32 tx, int32 ty, Pixel c1, Pixel c2, bool gradient, bool isPie)
{
    SKIA_TRACE()
    SkPath path = _skia_makePath(xPoints, yPoints, nPoints);

    backPaint.setColor(c1);
    if (gradient) {
        int32 minY, maxY;
        _skia_getPathBounds(xPoints, yPoints, nPoints, &minY, &maxY);
        SkPoint points[2] = {
                SkPoint::Make(xPoints[0], minY),
                SkPoint::Make(xPoints[0], maxY),
        };
        SkColor colors[2] = {c1, c2};
        backPaint.setShader(SkGradientShader::MakeLinear(
                points, colors, nullptr, 2,
                SkShader::kClamp_TileMode, 0, nullptr));
    }

    canvas->translate(tx, ty);
    canvas->drawPath(path, backPaint);
    canvas->translate(-tx, -ty);

    if (gradient) {
        backPaint.setShader(nullptr);
    }
}

// Adapted from SkPathPriv::CreateDrawArcPath
SkPath _skia_makeArcPath(const SkRect& oval, SkScalar startAngle, SkScalar sweepAngle, bool useCenter) {
    SkASSERT(!oval.isEmpty());
    SkASSERT(sweepAngle);

    SkPath path;
    path.setIsVolatile(true);
    path.setFillType(SkPath::kWinding_FillType);
    path.reset();
    if (SkScalarAbs(sweepAngle) >= 360.f) {
        path.addOval(oval);
        return path;
    }
    if (useCenter) {
        path.moveTo(oval.centerX(), oval.centerY());
    }
    // Arc to mods at 360 and drawArc is not supposed to.
    bool forceMoveTo = !useCenter;
    while (sweepAngle <= -360.f) {
        path.arcTo(oval, startAngle, -180.f, forceMoveTo);
        startAngle -= 180.f;
        path.arcTo(oval, startAngle, -180.f, false);
        startAngle -= 180.f;
        forceMoveTo = false;
        sweepAngle += 360.f;
    }
    while (sweepAngle >= 360.f) {
        path.arcTo(oval, startAngle, 180.f, forceMoveTo);
        startAngle += 180.f;
        path.arcTo(oval, startAngle, 180.f, false);
        startAngle += 180.f;
        forceMoveTo = false;
        sweepAngle -= 360.f;
    }
    path.arcTo(oval, startAngle, sweepAngle, forceMoveTo);
    if (useCenter) {
        path.close();
    }

    return path;
}
void skia_arcPiePointDrawAndFill(int32 skiaSurface, int32 xc, int32 yc, int32 rx, int32 ry, double startAngle, double endAngle, Pixel c, Pixel c2, bool fill, bool pie, bool gradient)
{
    double start = -startAngle;
    double sweepAngle = -(endAngle - startAngle);
    SKIA_TRACE()
    if (fill) {
        backPaint.setColor(c2);
        if (gradient) {
            SkPath arcPath = _skia_makeArcPath(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), start, sweepAngle, pie);
            SkRect r = arcPath.computeTightBounds();

            SkPoint points[2] = {
                SkPoint::Make(r.centerX(), r.y()),
                SkPoint::Make(r.centerX(), r.y() + r.height() * 2)
            };
            SkColor colors[2] = {c, c2};
            backPaint.setShader(SkGradientShader::MakeLinear(
                    points, colors, nullptr, 3,
                    SkShader::kClamp_TileMode, 0, nullptr));

            canvas->drawPath(arcPath, backPaint);
            backPaint.setShader(nullptr);
        } else {
            canvas->drawArc(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), start, sweepAngle, pie, backPaint);
            forePaint.setColor(c);
            SkScalar strokeWidth = forePaint.getStrokeWidth();
            forePaint.setStrokeWidth(2);
            canvas->drawArc(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), start, sweepAngle, pie, forePaint);
            forePaint.setStrokeWidth(strokeWidth);
        }
    } else {
        forePaint.setColor(c);
        canvas->drawArc(SkRect::MakeXYWH(xc - rx, yc - ry, rx * 2, ry * 2), start, sweepAngle, pie, forePaint);
    }
}

void skia_drawRoundRect(int32 skiaSurface, int32 x, int32 y, int32 w, int32 h, int32 r, Pixel c)
{
    SKIA_TRACE()
    forePaint.setColor(c);
    canvas->drawRRect(SkRRect::MakeRectXY(SkRect::MakeXYWH(x, y, w, h), r, r), forePaint);
}

void skia_fillRoundRect(int32 skiaSurface, int32 x, int32 y, int32 w, int32 h, int32 r, Pixel c)
{
    SKIA_TRACE()
    backPaint.setColor(c);
    canvas->drawRRect(SkRRect::MakeRectXY(SkRect::MakeXYWH(x, y, w, h), r, r), backPaint);
}

void skia_drawRoundGradient(int32 skiaSurface, int32 startX, int32 startY, int32 endX, int32 endY, int32 topLeftRadius, int32 topRightRadius, int32 bottomLeftRadius, int32 bottomRightRadius, int32 startColor, int32 endColor, bool vertical)
{
    SKIA_TRACE()
    int32 w = endX - startX;
    int32 h = endY - startY;
    SkPoint points[2];
    if (vertical) {
        points[0] = SkPoint::Make(startX, startY);
        points[1] = SkPoint::Make(startX, startY + h * 2);
    } else {
        points[0] = SkPoint::Make(startX, startY);
        points[1] = SkPoint::Make(startX + w * 2, startY);
    }

    SkColor colors[2] = {static_cast<SkColor>(startColor), static_cast<SkColor>(endColor)};
    backPaint.setShader(SkGradientShader::MakeLinear(
            points, colors, nullptr, 3,
            SkShader::kClamp_TileMode, 0, nullptr));

    canvas->drawRRect(SkRRect::MakeRectXY(SkRect::MakeXYWH(startX, startY, w, h), topLeftRadius, topLeftRadius), backPaint);
    backPaint.setShader(nullptr);
}
int skia_getsetRGB(int32 skiaSurface, void *pixels, int32 offset, int32 x, int32 y, int32 w, int32 h, bool isGet)
{
    SKIA_TRACE()
    // SkImageInfo info = SkImageInfo::MakeN32Premul(w, h);

    SkBitmap bitmap;
    // bitmap.installPixels(SkImageInfo::Make(w, h, kN32_SkColorType, kUnpremul_SkAlphaType), (void*)pixels, sizeof(Pixel) * w, nullptr, nullptr);

    // SkBitmap bitmap;
    bitmap.allocPixels(SkImageInfo::MakeN32Premul(w, h));
    if (isGet) {
        return canvas->readPixels(bitmap, x, y);
    } else {
        return canvas->writePixels(bitmap, x, y);
    }

    // Pixel pixel = bitmap.getAddr32(0, 0)[0];
    // return (((pixel >> 24) & 0xFF) << 24) | (((pixel & 0xFF) << 16) | (((pixel >> 8) & 0xFF) << 8) | ((pixel >> 16) & 0xFF));

    // if (isGet) {
    //     return canvas->readPixels(info, pixels, info.minRowBytes(), x, y);
    // } else {
    //     return canvas->writePixels(info, pixels, info.minRowBytes(), x, y);
    // }
}

void skia_shiftScreen(int32 x, int32 y) {
    canvas->translate(x, y);
    flushSkia();
}

#ifdef ANDROID
/**
 * Draws something into the given bitmap
 * @param  env
 * @param  thiz
 * @param  dstBitmap   The bitmap to place the results of skia into
 * @param  elapsedTime The number of milliseconds since the app was started
 */
extern "C" JNIEXPORT void JNICALL Java_totalcross_Launcher4A_drawIntoBitmap(JNIEnv *env,
                                                                            jobject thiz, jobject dstBitmap, jlong elapsedTime)
{
    // Grab the dst bitmap info and pixels
    AndroidBitmapInfo dstInfo;
    void *dstPixels;
    AndroidBitmap_getInfo(env, dstBitmap, &dstInfo);
    AndroidBitmap_lockPixels(env, dstBitmap, &dstPixels);

    SkImageInfo info = SkImageInfo::MakeN32Premul(dstInfo.width, dstInfo.height);

    // write from canvas to the screen bitmap
    if (canvas != NULL)
    {
        bool ret = canvas->readPixels(info, dstPixels, dstInfo.stride, 0, 0);
    }
    // Unlock the dst's pixels
    AndroidBitmap_unlockPixels(env, dstBitmap);
}
#endif
