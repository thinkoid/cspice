/*

-Procedure rotate_c ( Generate a rotation matrix )

-Abstract

   Calculate the 3x3 rotation matrix generated by a rotation
   of a specified angle about a specified axis. This rotation
   is thought of as rotating the coordinate system.

-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading

   None.

-Keywords

   MATRIX
   ROTATION

*/

   #include <cspice/SpiceZfc.h>
   #include <cspice/SpiceUsr.h>
   #include <cspice/SpiceZmc.h>

   void rotate_c ( SpiceDouble     angle,
                   SpiceInt        iaxis,
                   SpiceDouble     mout[3][3] )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   angle      I   Angle of rotation (radians).
   iaxis      I   Axis of rotation (X=1, Y=2, Z=3).
   mout       O   Resulting rotation matrix [angle]
                                                   iaxis

-Detailed_Input

   angle       is the angle given in radians, through which the rotation
               is performed.

   iaxis       is the index of the axis of rotation. The X, Y, and Z
               axes have indices 1, 2 and 3 respectively.

-Detailed_Output

   mout        is the rotation matrix which describes the rotation of the
               COORDINATE system through angle radians about the
               axis whose index is iaxis.

-Parameters

   None.

-Exceptions

   Error free.

   1)  If the axis index is not in the range 1 to 3, it will be
       treated the same as that integer 1, 2, or 3 that is congruent
       to it mod 3.

-Files

   None.

-Particulars

   A rotation about the first, i.e. x-axis, is described by

      |  1        0          0      |
      |  0   cos(theta) sin(theta)  |
      |  0  -sin(theta) cos(theta)  |

   A rotation about the second, i.e. y-axis, is described by

      |  cos(theta)  0  -sin(theta)  |
      |      0       1        0      |
      |  sin(theta)  0   cos(theta)  |

   A rotation about the third, i.e. z-axis, is described by

      |  cos(theta) sin(theta)   0   |
      | -sin(theta) cos(theta)   0   |
      |       0          0       1   |

   rotate_c decides which form is appropriate according to the value
   of IAXIS.

-Examples

   If rotate_c is called from a C program as follows:

         rotate_c ( pi_c()/4, 3, mout );

   then mout will be given by

                | sqrt(2)/2   sqrt(2)/2   0  |
         mout = |-sqrt(2)/2   sqrt(2)/2   0  |
                |     0           0       1  |

-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   J. Diaz del Rio     (ODC Space)

-Version

   -CSPICE Version 1.0.1, 04-AUG-2021 (JDR)

       Edited the header to comply with NAIF standard.

   -CSPICE Version 1.0.0, 08-FEB-1998 (NJB)

       Based on SPICELIB Version 1.0.1, 10-MAR-1992 (WLT)

-Index_Entries

   generate a rotation matrix

-&
*/

{ /* Begin rotate_c */

   /*
   Local variables
   */
   SpiceDouble             loc_mat[3][3];


   /*
   Call the f2c'd version of the routine.
   */
   rotate_ ( (doublereal *) &angle,
             (integer    *) &iaxis,
             (doublereal *)  loc_mat );

   /*
   Transpose the output matrix to put it in row-major order.
   */
   xpose_c ( loc_mat, loc_mat );


   /*
   Set the output argument.
   */
   MOVED ( loc_mat, 9, mout );


} /* End rotate_c */
