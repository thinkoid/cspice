/*

-Procedure filli_c ( Fill an integer array )

-Abstract

   Fill an integer array with a specified value.

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

   ARRAY
   ASSIGNMENT

*/
   #include <cspice/SpiceUsr.h>


   void filli_c  ( SpiceInt            value,
                   SpiceInt            ndim,
                   SpiceInt            array  [] )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   value      I   Integer value to be placed in all the elements of
                  `array'.
   ndim       I   The number of elements in `array'.
   array      O   Integer array which is to be filled.

-Detailed_Input

   value       is the value to be assigned to the array elements
               0 through ndim - 1.

   ndim        is the number of elements in the array.

-Detailed_Output

   array       is an integer array whose elements are to be set
               to `value'.

-Parameters

   None.

-Exceptions

   Error free.

   1)  If ndim < 1, the array is not modified.

-Files

   None.

-Particulars

   None.

-Examples

   The numerical results shown for this example may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) Initialize all members of an integer array to the same value.


      Example code begins here.


      /.
         Program filli_ex1
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {

         /.
         Local parameters.
         ./
         #define NDIM         4

         /.
         Local variables.
         ./
         SpiceInt             array  [NDIM];
         SpiceInt             i;

         /.
         Initialize all members of the array `array' to 11, and
         print out its contents.
         ./
         filli_c ( 11, NDIM, array );

         printf( "Contents of ARRAY:\n" );
         for ( i = 0; i < NDIM; i++ )
         {
            printf( "   Index: %1d; value: %2d\n", (int)i, (int)array[i] );
         }

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Contents of ARRAY:
         Index: 0; value: 11
         Index: 1; value: 11
         Index: 2; value: 11
         Index: 3; value: 11


-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   J. Diaz del Rio     (ODC Space)

-Version

   -CSPICE Version 1.0.0, 19-FEB-2021 (JDR)

-Index_Entries

   fill an integer array

-&
*/

{ /* Begin filli_c */

   /*
   Error free:  no error tracing required.
   */

   /*
   Local variables
   */
   SpiceInt                i;


   for ( i = 0;  i < ndim;  i++ )
   {
      array[i] = value;
   }

} /* End filli_c */
