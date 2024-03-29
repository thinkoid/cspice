/*

-Procedure tyear_c ( Seconds per tropical year )

-Abstract

   Return the number of seconds in a tropical year.

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

   CONSTANTS

*/

   #include <cspice/SpiceUsr.h>

   SpiceDouble tyear_c ( void )

/*

-Brief_I/O

   The function returns the number of seconds per tropical year.

-Detailed_Input

   None.

-Detailed_Output

   The function returns the number of seconds per tropical
   year. This value is taken from the 1992 Explanatory Supplement
   to the Astronomical Almanac (see [1]).

-Parameters

   None.

-Exceptions

   Error free.

-Files

   None.

-Particulars

   The tropical year is often used as a fundamental unit
   of time when dealing with older ephemeris data. For this
   reason its value in terms of ephemeris seconds is
   recorded in this function.

-Examples

   The numerical results shown for these examples may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) Display the double precision value of the number of seconds in a
      tropical year.

      Example code begins here.


      /.
         Program tyear_ex1
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {
         /.
         Display the number of seconds in a tropical year,
         in 16.3 floating point format
         ./
         printf ( "Seconds per tropical year: %20.8f\n", tyear_c() );

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Seconds per tropical year:    31556925.97470000


   2) Suppose you wish to compute the number of tropical centuries
      that have elapsed since the ephemeris epoch B1950 (beginning
      of the Besselian year 1950) at a particular UTC epoch.

      Use the LSK kernel below to load the leap seconds and time
      constants required for the conversions.

         naif0012.tls


      Example code begins here.


      /.
         Program tyear_ex2
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {
         /.
         Local constants.
         ./
         #define        UTCSTR        "2044-JUL-31"

         /.
         Local variables.
         ./
         SpiceDouble             et;
         SpiceDouble             centur;

         /.
         Load the LSK file.
         ./
         furnsh_c ( "naif0012.tls" );

         /.
         Convert input UTC string to Ephemeris Time.
         ./
         str2et_c ( UTCSTR, &et );
         printf ( "Input ephemeris time         : %16.3f\n", et );


         centur = ( et - unitim_c ( b1950_c(), "JED", "ET" ) );
         centur = centur / ( 100.0 * tyear_c() );

         printf ( "Tropical centuries past B1950: %16.10f\n", centur );

         return ( 0 );

      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Input ephemeris time         :   1406808069.183
      Tropical centuries past B1950:     0.9458128731


-Restrictions

   None.

-Literature_References

   [1]  P. Kenneth Seidelmann (Ed.), "Explanatory Supplement to the
        Astronomical Almanac," p 80, University Science Books, 1992.

-Author_and_Institution

   J. Diaz del Rio     (ODC Space)
   W.L. Taber          (JPL)
   E.D. Wright         (JPL)

-Version

   -CSPICE Version 1.0.1, 05-JUL-2021 (JDR)

       Edited the header to comply with NAIF standard. Added
       complete code examples.

   -CSPICE Version 1.0.0, 08-FEB-1998 (EDW) (WLT)

-Index_Entries

   Number of seconds per tropical year

-&
*/

{ /* Begin tyear_c */

   return 31556925.9747;

} /* End tyear_c */
