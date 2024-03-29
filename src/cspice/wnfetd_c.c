/*

-Procedure wnfetd_c ( Fetch an interval from a DP window )

-Abstract

   Fetch a particular interval from a double precision window.

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

   WINDOWS

-Keywords

   WINDOWS

*/

   #include <cspice/SpiceUsr.h>
   #include <cspice/SpiceZfc.h>
   #include <cspice/SpiceZmc.h>


   void wnfetd_c ( SpiceCell    * window,
                   SpiceInt       n,
                   SpiceDouble  * left,
                   SpiceDouble  * right   )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   window     I   Input window.
   n          I   Index of interval to be fetched.
   left,
   right      O   Left, right endpoints of the nth interval.

-Detailed_Input

   window      is a window containing zero or more intervals.

               `window' must be declared as a double precision SpiceCell.

               CSPICE provides the following macro, which declares and
               initializes the cell

                  SPICEDOUBLE_CELL        ( window, WINDOWSZ );

               where WINDOWSZ is the maximum capacity of `window'.

   n           is the index of a particular interval within the window.
               Indices range from 0 to NINT-1, where NINT is the number of
               intervals in the window (card_c(&window)/2).

-Detailed_Output

   left,
   right       are the left and right endpoints of the N'th interval in
               the input window. If the interval is not found, `left' and
               `right' are not defined.

-Parameters

   None.

-Exceptions

   1)  If `n' is less than one, the error SPICE(NOINTERVAL) is
       signaled by a routine in the call tree of this routine.

   2)  If the interval does not exist, i.e. n > card_c(window)/2, the
       error SPICE(NOINTERVAL) is signaled by a routine in the call
       tree of this routine.

   3)  The cardinality of the input `window' must be even. Left
       endpoints of stored intervals must be strictly greater than
       preceding right endpoints. Right endpoints must be greater
       than or equal to corresponding left endpoints. Invalid window
       data are not diagnosed by this routine and may lead to
       unpredictable results.

   4)  If the `window' cell argument has a type other than
       SpiceDouble, the error SPICE(TYPEMISMATCH) is signaled.

-Files

   None.

-Particulars

   None.

-Examples

   The numerical results shown for this example may differ across
   platforms. The results depend on the SPICE kernels used as input,
   the compiler and supporting libraries, and the machine specific
   arithmetic implementation.

   1) The following code example demonstrates how to insert an
      interval into an existing double precision SPICE window, and
      how to loop over all its intervals to extract their left and
      right points.


      Example code begins here.


      /.
         Program wnfetd_ex1
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main()
      {

         /.
         Local parameters.
         ./
         #define WNSIZE          10

         /.
         Local variables.
         ./
         SpiceDouble              left;
         SpiceDouble              right;

         SPICEDOUBLE_CELL ( window,  WNSIZE );

         SpiceInt                 i;

         /.
         Validate the window with size WNSIZE and zero elements.
         ./
         wnvald_c ( WNSIZE, 0, &window );

         /.
         Insert the intervals

            [ 1, 3 ]  [ 7, 11 ]  [ 23, 27 ]

         into `window'.
         ./
         wninsd_c (  1.0,   3.0, &window );
         wninsd_c (  7.0,  11.0, &window );
         wninsd_c ( 23.0,  27.0, &window );

         /.
         Loop over the number of intervals in `window', output
         the `left' and `right' endpoints for each interval.
         ./
         for ( i=0; i<wncard_c(&window); i++)
         {
            wnfetd_c( &window, i, &left, &right );
            printf("Interval %d [%8.3f, %8.3f]\n", i, left, right );
         }

         return ( 0 );

      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Interval 0 [   1.000,    3.000]
      Interval 1 [   7.000,   11.000]
      Interval 2 [  23.000,   27.000]


-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   J. Diaz del Rio     (ODC Space)
   W.L. Taber          (JPL)
   I.M. Underwood      (JPL)
   E.D. Wright         (JPL)

-Version

   -CSPICE Version 1.0.2, 10-AUG-2021 (JDR)

       Edited the header to comply to NAIF standard. Added complete code
       example, problem statement and solution.

       Extended description of argument "window" in -Detailed_Input to include
       type and preferred declaration method.

       Added entry #3 in -Exceptions section.

   -CSPICE Version 1.0.1, 30-JUL-2007 (EDW)

      Removed erroneous description in the -Examples section
      indicating "Undefined" as a return state after an error
      event caused by an invalid value of n.

   -CSPICE Version 1.0.0, 22-AUG-2002 (NJB) (WLT) (IMU)

-Index_Entries

   fetch an interval from a d.p. window

-&
*/

{ /* Begin wnfetd_c */


   /*
   Local variables
   */
   SpiceInt                fn;

   /*
   Participate in error tracing.
   */
   if ( return_c() )
      {
      return;
      }
   chkin_c ( "wnfetd_c" );


   /*
   Make sure the window's data type is d.p.
   */
   CELLTYPECHK ( CHK_STANDARD, "wnfetd_c", SPICE_DP, window );


   /*
   Initialize the cell if necessary.
   */
   CELLINIT ( window );

   /*
   Map the index to a Fortran-style index.
   */
   fn = n + 1;

   wnfetd_ ( ( doublereal * ) window->base,
             ( integer    * ) &fn,
             ( doublereal * ) left,
             ( doublereal * ) right        );


   chkout_c ( "wnfetd_c" );

} /* End wnfetd_c */
