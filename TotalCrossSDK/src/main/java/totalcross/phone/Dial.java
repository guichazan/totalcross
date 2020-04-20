/*********************************************************************************
 *  TotalCross Software Development Kit                                          *
 *  Copyright (C) 2000-2012 SuperWaba Ltda.                                      *
 *  Copyright (C) 2012-2020 TotalCross Global Mobile Platform Ltda.   
 *  All Rights Reserved                                                          *
 *                                                                               *
 *  This library and virtual machine is distributed in the hope that it will     *
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                         *
 *                                                                               *
 *  This file is covered by the GNU LESSER GENERAL PUBLIC LICENSE VERSION 2.1    *
 *  A copy of this license is located in file license.txt at the root of this    *
 *  SDK or can be downloaded here:                                               *
 *  http://www.gnu.org/licenses/lgpl-2.1.txt                                     *
 *                                                                               *
 *********************************************************************************/

package totalcross.phone;

import com.totalcross.annotations.ReplacedByNativeOnDeploy;
import totalcross.io.IOException;

/** Used to dial a number in a smartphone.
 * A single listener can receive messages from the system informing the current status.
 * Currently works on Android, and iOS.
 *
 * @since TotalCross 1.0
 */

final public class Dial {
  /** 
   * A dial listener that will receive events informing the actual status of the dialing.
   * Does not work on the currently supported platforms.  
   * @deprecated */
  @Deprecated
  public static interface Listener {
    public void dialStatusChange(String msg);
  }

  /** The listener that will receive status change messages. Does not work on the currently supported platforms.  */
  public static Listener listener;

  /** Dials the given number. */
  @ReplacedByNativeOnDeploy
  public static void number(String number) throws IOException {
  }

  /** Hangs up a running call. Does not work on the currently supported platforms. 
   * @deprecated*/
  @Deprecated
  @ReplacedByNativeOnDeploy
  public static void hangup() {
  }
}
