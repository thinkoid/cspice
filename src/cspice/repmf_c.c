/*

-Procedure repmf_c  ( Replace marker with formatted d.p. value )

-Abstract

   Replace a marker in a string with a formatted double precision
   value.

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

   CHARACTER
   CONVERSION
   STRING

*/

   #include <cspice/SpiceUsr.h>
   #include <cspice/SpiceZfc.h>
   #include <cspice/SpiceZst.h>
   #include <cspice/SpiceZmc.h>

   void repmf_c ( ConstSpiceChar     * in,
                  ConstSpiceChar     * marker,
                  SpiceDouble          value,
                  SpiceInt             sigdig,
                  SpiceChar            format,
                  SpiceInt             outlen,
                  SpiceChar          * out )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   in         I   Input string.
   marker     I   Marker to be replaced.
   value      I   Replacement value.
   sigdig     I   Significant digits in replacement text.
   format     I   Format: 'E' or 'F'.
   outlen     I   Available space in output string.
   out        O   Output string.
   MAXLFD     P   Maximum length of a formatted DP number.

-Detailed_Input

   in          is an arbitrary character string.

   marker      is an arbitrary character string. The first occurrence of
               `marker' in the input string is to be replaced by `value'.

               Leading and trailing blanks in `marker' are NOT
               significant. In particular, no substitution is performed
               if `marker' is blank or empty.

   value       is an arbitrary double precision number.

   sigdig      is the number of significant digits with which `value' is
               to be represented. `sigdig' must be greater than zero and
               less than 15.

   format      is the format in which `value' is to be represented. `format'
               may be any of the following:

                  format   Meaning                 Example
                  ------   ---------------------   -----------
                  E, e     Scientific (exponent)   3.14159E+03
                           notation

                  F, f     Fixed-point notation    3141.59

   outlen      is the maximum allowed length of the output string `out'.
               This length must be large enough to hold the output string
               plus the null-terminator character. If the output string
               is expected to have N characters, `outlen' should be at
               least N+1.

-Detailed_Output

   out         is the string obtained by substituting the text
               representation of `value' for the first occurrence of
               `marker' in the input string.

               The text representation of `value' is in scientific
               (exponent) or fixed-point notation, depending on having
               the value of `format', and having the number of significant
               digits specified by `sigdig'. The representation of `value'
               is produced by the SPICELIB routine DPSTRF; see that
               routine for details concerning the representation of
               double precision numbers.

               `out' and `in' must be identical or disjoint.

-Parameters

   MAXLFD      is the maximum expected length of the text representation
               of a formatted double precision number. 56 characters are
               sufficient to hold any result returned by the SPICELIB
               routine DPSTRF. (See -Restrictions)

-Exceptions

   1)  If `out' does not have sufficient length to accommodate the
       result of the substitution, the result will be truncated on
       the right.

   2)  If `marker' is blank or empty, or if `marker' is not a substring of
       `in', this routine leaves the input string unchanged, except that
       trailing blanks will be trimmed. This case is not considered an error.

   3)  If `format' is anything other than 'E', this routine defaults
       to 'F'. This is not considered an error.

   4)  If any of the `in' or `marker' input string pointers is null,
       the error SPICE(NULLPOINTER) is signaled.

   5)  If the `out' output string pointer is null, the error
       SPICE(NULLPOINTER) is signaled.

   6)  If the `out' output string has length less than one character,
       the error SPICE(STRINGTOOSHORT) is signaled.

-Files

   None.

-Particulars

   This is one of a family of related routines for inserting values
   into strings. They are typically to construct messages that
   are partly fixed, and partly determined at run time. For example,
   a message like

      "Fifty-one pictures were found in directory [USER.DATA]."

   might be constructed from the fixed string

      "#1 pictures were found in directory #2."

   by the calls

      repmct_c ( string, "#1",  51,  'c',      lenstr, string );
      repmc_c  ( string, "#2", "[USER.DATA]",  lenstr, string );

   which substitute the cardinal text "Fifty-one" and the character
   string "[USER.DATA]" for the markers "#1" and "#2" respectively.

   The complete list of routines is shown below.

      repmc_c    ( Replace marker with character string value )
      repmd_c    ( Replace marker with double precision value )
      repmf_c    ( Replace marker with formatted d.p. value   )
      repmi_c    ( Replace marker with integer value          )
      repml_c    ( Replace marker with logical value          )
      repmct_c   ( Replace marker with cardinal text          )
      repmot_c   ( Replace marker with ordinal text           )

-Examples

   The numerical results shown for this example may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) The following example illustrate the use of repmf_c to
      replace a marker within a string with a formatted double
      precision value.


      Example code begins here.


      /.
         Program repmf_ex1
      ./
      #include <stdio.h>
      #include <string.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {

         /.
         Local parameters.
         ./
         #define STRLEN       81

         /.
         Local variables.
         ./
         SpiceChar            instr  [STRLEN];
         SpiceChar            marker [STRLEN];
         SpiceChar            outstr [STRLEN];

         /.
         1. Single marker, two significant digits, scientific.
         ./
         strncpy( marker, "#", 2 );
         strncpy( instr, "Invalid value. The value was:  #", 33 );

         repmf_c ( instr, marker, 5.0e1, 2, 'E', STRLEN, outstr );

         printf( "Case 1: Single marker, two significant digits, "
                 "scientific.\n" );
         printf( "   Input : %s\n", instr );
         printf( "   Output: %s\n", outstr );
         printf( "\n" );

         /.
         2. Multiple markers, three significant digits,
            scientific.
         ./
         strncpy( marker, " XX ", 5 );
         strncpy( instr, "Left > Right endpoint. Left: XX; Right: XX", 43 );

         repmf_c ( instr, marker, -5.2e-9, 3, 'e', STRLEN, outstr );

         printf( "Case 2: Multiple markers, 3 significant digits, "
                 "scientific.\n" );
         printf( "   Input : %s\n", instr );
         printf( "   Output: %s\n", outstr );
         printf( "\n" );

         /.
         3. Fixed-point notation.
         ./
         strncpy( marker, "#", 2 );
         strncpy( instr, "Invalid value. The value was:  #", 33 );

         repmf_c ( instr, marker, 5.0e1, 3, 'F', STRLEN, outstr );

         printf( "Case 3: Fixed-point notation.\n" );
         printf( "   Input : %s\n", instr );
         printf( "   Output: %s\n", outstr );
         printf( "\n" );

         /.
         4. Fixed-point notation, no decimals.
         ./
         strncpy( marker, "#", 2 );
         strncpy( instr, "Invalid value. The value was:  #", 33 );

         repmf_c ( instr, marker, 5.0e1, 2, 'f', STRLEN, outstr );

         printf( "Case 4: Fixed-point notation, no decimals.\n" );
         printf( "   Input : %s\n", instr );
         printf( "   Output: %s\n", outstr );
         printf( "\n" );

         /.
         5. Excessive significant digits.
         ./
         strncpy( marker, "#", 2 );
         strncpy( instr, "Invalid value. The value was:  #", 33 );

         repmf_c ( instr, marker, 5.0e1, 100, 'F', STRLEN, outstr );

         printf( "Case 5: Excessive significant digits.\n" );
         printf( "   Input : %s\n", instr );
         printf( "   Output: %s\n", outstr );
         printf( "\n" );

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Case 1: Single marker, two significant digits, scientific.
         Input : Invalid value. The value was:  #
         Output: Invalid value. The value was:  5.0E+01

      Case 2: Multiple markers, 3 significant digits, scientific.
         Input : Left > Right endpoint. Left: XX; Right: XX
         Output: Left > Right endpoint. Left: -5.20E-09; Right: XX

      Case 3: Fixed-point notation.
         Input : Invalid value. The value was:  #
         Output: Invalid value. The value was:  50.0

      Case 4: Fixed-point notation, no decimals.
         Input : Invalid value. The value was:  #
         Output: Invalid value. The value was:  50.

      Case 5: Excessive significant digits.
         Input : Invalid value. The value was:  #
         Output: Invalid value. The value was:  50.000000000000


      Note that, in Case #5 even though 100 digits of precision were
      requested, only 14 were returned.

-Restrictions

   1)  The maximum number of significant digits returned is 14.

   2)  This routine makes explicit use of the format of the string
       returned by the SPICELIB routine DPSTRF; should that routine
       change, substantial work may be required to bring this routine
       back up to snuff.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   J. Diaz del Rio     (ODC Space)
   I.M. Underwood      (JPL)

-Version

   -CSPICE Version 1.0.1, 01-NOV-2021 (JDR)

       Changed input argument name "lenout" to "outlen" for consistency
       with other routines.

       Edited the header to comply with NAIF standard. Added complete
       code example based on existing fragments of code.

       Updated -Exceptions entry #5 text.

   -CSPICE Version 1.0.0, 14-AUG-2002 (NJB) (IMU)

-Index_Entries

   replace marker with formatted d.p. value

-&
*/

{ /* Begin repmf_c */


   /*
   Local variables
   */
   ConstSpiceChar        * markPtr;


   /*
   Use discovery check-in.

   Make sure no string argument pointers are null.
   */
   CHKPTR( CHK_DISCOVER, "repmf_c", in     );
   CHKPTR( CHK_DISCOVER, "repmf_c", marker );
   CHKPTR( CHK_DISCOVER, "repmf_c", out    );



   /*
   If the output string can't hold a terminating null character,
   we can't proceed.
   */
   if ( outlen < 1 )
   {
      chkin_c  ( "repmf_c"                                    );
      setmsg_c ( "String length outlen must be >= 1; actual "
                 "value = #."                                 );
      errint_c ( "#", outlen                                  );
      sigerr_c ( "SPICE(STRINGTOOSHORT)"                      );
      chkout_c ( "repmf_c"                                    );
      return;
   }


   /*
   If the output string has no room for data characters, we simply
   terminate the string.
   */
   if ( outlen == 1 )
   {
      out[0] = NULLCHAR;
      return;
   }


   /*
   If the input string has zero length, the output is empty as well.
   */
   if ( in[0] == NULLCHAR )
   {
      out[0] = NULLCHAR;

      return;
   }


   /*
   If the marker is empty, pass a blank marker to the f2c'd routine.
   Otherwise, pass in the marker.
   */
   if ( marker[0] == NULLCHAR )
   {
      markPtr = " ";
   }
   else
   {
      markPtr = marker;
   }


   /*
   Simply call the f2c'd routine.
   */
   repmf_ ( ( char        * ) in,
            ( char        * ) marker,
            ( doublereal  * ) &value,
            ( integer     * ) &sigdig,
            ( char        * ) &format,
            ( char        * ) out,
            ( ftnlen        ) strlen(in),
            ( ftnlen        ) strlen(markPtr),
            ( ftnlen        ) 1,
            ( ftnlen        ) outlen-1        );

   /*
   Convert the output string from Fortran to C style.
   */
   F2C_ConvertStr ( outlen, out );


} /* End repmf_c */
