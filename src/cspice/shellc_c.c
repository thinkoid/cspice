/*

-Procedure shellc_c ( Shell sort a character array )

-Abstract

   Sort an array of character strings according to the ASCII
   collating sequence using the Shell Sort algorithm.

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
   SORT

*/

   #include <stdlib.h>
   #include <cspice/SpiceUsr.h>
   #include <cspice/SpiceZfc.h>
   #include <cspice/SpiceZst.h>
   #include <cspice/SpiceZmc.h>

   void shellc_c ( SpiceInt     ndim,
                   SpiceInt     arrlen,
                   void       * array   )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   ndim       I   Dimension of the array.
   arrlen     I   String length.
   array     I-O  The array.

-Detailed_Input

   ndim        is the number of elements in the array to be sorted.

   arrlen      is the declared length of the strings in the input
               string array, including null terminators. The input
               array should be declared with dimension

                  [ndim][arrlen]

   array       on input, is the array to be sorted.

-Detailed_Output

   array       on output, contains the same elements, sorted
               according to the ASCII collating sequence.
               The actual sorting is done in place in array.

-Parameters

   None.

-Exceptions

   1)  If ndim < 2, this routine does not modify the array.

   2)  If the `array' input array pointer is null, the error
       SPICE(NULLPOINTER) is signaled.

   3)  If the `array' input array strings have length less than two
       characters, the error SPICE(STRINGTOOSHORT) is signaled.

-Files

   None.

-Particulars

   The Shell Sort Algorithm is well known.

-Examples

   Let array contain the following elements:

      "FEYNMAN"
      "NEWTON"
      "EINSTEIN"
      "GALILEO"
      "EUCLID"
      "Galileo"

   Then after a call to shellc_c, the array would be ordered as
   follows:

      "EINSTEIN"
      "EUCLID"
      "FEYNMAN"
      "GALILEO"
      "Galileo"
      "NEWTON"

-Restrictions

   1)  The input array is assumed to be sorted in increasing order. If
       this condition is not met, the results of bsrchc_c are unpredictable.

   2)  String comparisons performed by this routine are Fortran-style:
       trailing blanks in the input array or key value are ignored.
       This gives consistent behavior with CSPICE code generated by
       the f2c translator, as well as with the Fortran SPICE Toolkit.

       Note that this behavior is not identical to that of the ANSI
       C library functions strcmp and strncmp.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   J. Diaz del Rio     (ODC Space)
   I.M. Underwood      (JPL)

-Version

   -CSPICE Version 1.1.0, 05-AUG-2021 (JDR)

       Changed the input argument name "lenvals" to "arrlen" for consistency
       with other routines.

       Edited the header to comply with NAIF standard.

   -CSPICE Version 1.0.0, 18-JUL-2002 (NJB) (IMU)

-Index_Entries

   shell sort a character array

-&
*/

{ /* Begin shellc_c */


   /*
   Local variables
   */
   SpiceChar             * fCvalsArr;

   SpiceInt                fCvalsLen;
   SpiceInt                nBytes;



   /*
   Use discovery check-in.

   Return immediately if no re-ordering is required.
   */
   if ( ndim < 2 )
   {
      return;
   }

   /*
   Make sure the input pointer for the string array is non-null
   and that the length arrlen is sufficient.
   */
   CHKOSTR ( CHK_DISCOVER, "shellc_c", array, arrlen );

   /*
   Create a Fortran-style string array.  Don't eliminate trailing
   white space during translation, since it will be convenient to keep the
   same array dimensions when we return the sorted array.
   */
   C2F_MapFixStrArr ( "shellc_c",
                      ndim, arrlen, array, &fCvalsLen, &fCvalsArr );

   if ( failed_c() )
   {
      return;
   }

   /*
   Call the f2c'd routine.
   */
   shellc_ (  ( integer    * ) &ndim,
              ( char       * ) fCvalsArr,
              ( ftnlen       ) fCvalsLen  );


   /*
   Copy the Fortran array into the output array.
   */
   nBytes = ndim * fCvalsLen * sizeof(SpiceChar);

   memmove ( array, fCvalsArr, nBytes );


   /*
   Free the dynamically allocated array.
   */
   free ( fCvalsArr );

   /*
   Convert the output array from Fortran to C style.
   */
   F2C_ConvertTrStrArr ( ndim, arrlen, (SpiceChar *)array );


} /* End shellc_c */
