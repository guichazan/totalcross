/*********************************************************************************
 *  TotalCross Software Development Kit                                          *
 *  Copyright (C) 2000-2012 SuperWaba Ltda.                                      *
 *  Copyright (C) 2012-2020 TotalCross Global Mobile Platform Ltda.              *
 *  All Rights Reserved                                                          *
 *                                                                               *
 *  This library and virtual machine is distributed in the hope that it will     *
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                         *
 *                                                                               *
 *  This file is covered by the GNU LESSER GENERAL PUBLIC LICENSE VERSION 3.0    *
 *  A copy of this license is located in file license.txt at the root of this    *
 *  SDK or can be downloaded here:                                               *
 *  http://www.gnu.org/licenses/lgpl-3.0.txt                                     *
 *                                                                               *
 *********************************************************************************/

package tc.tools.converter.bb.attribute;

import tc.tools.converter.bb.JavaClass;
import tc.tools.converter.bb.JavaConstant;
import totalcross.io.DataStream;
import totalcross.io.IOException;
import totalcross.util.Vector;

public class Exceptions implements AttributeInfo {
  private JavaClass jclass;

  public Vector exceptions;

  public Exceptions(JavaClass jclass) {
    this.jclass = jclass;
    exceptions = new Vector();
  }

  @Override
  public int length() {
    return 2 + (exceptions.size() * 2);
  }

  @Override
  public void load(DataStream ds) throws IOException {
    int count = ds.readUnsignedShort();
    exceptions.removeAllElements();
    for (int i = 0; i < count; i++) {
      exceptions.addElement(jclass.getConstant(ds.readUnsignedShort(), this));
    }
  }

  @Override
  public void save(DataStream ds) throws IOException {
    int count = exceptions.size();
    ds.writeShort(count);
    for (int i = 0; i < count; i++) {
      ds.writeShort(jclass.getConstantIndex((JavaConstant) exceptions.items[i], this));
    }
  }
}
