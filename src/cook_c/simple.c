/*

-Procedure simple (Simple program to demonstrate SPICE Toolkit)


-Abstract

   This "cookbook" program demonstrates the use of SPICE SPK ephemeris
   files and software.

   Although this program lacks sophistication, it can serve
   as a starting point from which you could build your own program.

   The CSPICE subroutine furnsh_c (Furnish a program with SPICE
   kernels) "loads" kernel files into the SPICE system. The calling
   program indicates which files to load by passing their names to
   furnsh_c.  It is also possible to supply furnsh_c with the name of a
   "metakernel" containing a list of files to load; see the header of
   furnsh_c for an example.

   spkezr_c (S/P Kernel, easier reader) computes states by by accessing
   the data loaded with furnsh_c (spkezr_c does not require the name of
   an SPK file as input).

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

-Input

   The user is prompted for the following input:

      - The name of a NAIF leapseconds kernel file.
      - The name of one binary NAIF SPK ephemeris file.
      - The name for the first target body.
      - The name for the second target body.
      - The name for the observing body.
      - A UTC time interval at which to determine states.

-Output

   The program calculates the angular separation of the two
   target bodies as seen from the observing body.

-Particulars

   The user enters the names for two target bodies and an
   observer (these may be any objects in the solar system for
   which the user has data) and the UTC time of interest.

   For the sake of brevity, this program NO error checking
   on its inputs. Mistakes will cause the program to crash.

-References

   See the cookbook routine states_c.c.

-Version

   -CSPICE Version 2.0.0, 12-NOV-2002   (EDW)

      Modified program to reproduce, as precisely as possible,
      output of the FORTRAN version of the SIMPLE cookbook.
      Programing style and brevity are secondary to this goal.

   -CSPICE Version 1.0.1, 04-JAN-2002   (EDW) 

      Removed unneeded variable 'format'.

   -CSPICE Version 1.0.0, 17-OCT-1999   (EDW) 
-&
*/


   /* Include needed headers. */

   #include <stdio.h>
   #include <cspice/SpiceUsr.h>

int main()
   {

   /*
   Local constants
   */

   #define                 FILE_SIZE 128
   #define                 WORD_SIZE  48
   #define                 MAXPTS     10

   /*
   Local variables
   */

   SpiceDouble             et;
   SpiceDouble             etbeg;
   SpiceDouble             etend;
   SpiceDouble             delta;
   SpiceDouble             lt1;
   SpiceDouble             lt2;
   SpiceDouble             state1 [6];
   SpiceDouble             state2 [6];
   SpiceDouble             x[MAXPTS];
   SpiceDouble             y[MAXPTS];

   SpiceChar               leap  [FILE_SIZE];
   SpiceChar               obs   [WORD_SIZE];
   SpiceChar               spk   [FILE_SIZE];
   SpiceChar               targ1 [WORD_SIZE];
   SpiceChar               targ2 [WORD_SIZE];
   SpiceChar               utctim[WORD_SIZE];
   SpiceChar               utcbeg[WORD_SIZE];
   SpiceChar               utcend[WORD_SIZE];
   SpiceChar               answer[WORD_SIZE];
   SpiceChar             * corr;
   SpiceChar             * ref;

   SpiceBoolean            cont;

   SpiceInt                i;

   puts (" ");
   puts (" "); 
   puts ("                    Welcome to SIMPLE"                  );
   puts (" "); 
   puts ("This program calculates the angular separation of two"  );
   puts ("target bodies as seen from an observing body."          );
   puts (" ");
   puts ("The angular separations are calculated for each of 10"  );
   puts ("equally spaced times in a given time interval. A table" );
   puts ("of the results is presented.");
   puts (" ");


   /*
   Set the time output format, the precision of that output
   and the reference frame.  Note:  The angular separation has the
   same value in all reference frames.  Let's use our favorite, J2000.
   We need an aberration correction.  "LT+S", light time plus stellar
   aberration, satisfies the requirements for this program.
   */
   ref    = "J2000";
   corr   = "LT+S";


   /*
   Get the various inputs using interactive prompts:
   */
   puts (" ");
   prompt_c ( "Enter the name of a leapseconds kernel file: ", 
                                                     WORD_SIZE, leap );
   puts (" ");

   /*
   First load the leapseconds file into the kernel pool, so
   we can convert the UTC time strings to ephemeris seconds
   past J2000.
   */
   furnsh_c ( leap );


   prompt_c ( "Enter the name of a binary SPK ephemeris file: ",
                                                     WORD_SIZE, spk  );

   /*
   Load the binary SPK file containing the ephemeris data
   that we need.
   */
   furnsh_c ( spk  );

   cont = SPICETRUE;

   /* Loop till the user quits. */
   do
      {

      /*
      Get the NAIF IDs for the two target bodies and the observing
      body.
      */

      puts(" ");
      prompt_c( "Enter the name of the observing body: ", 
                                                     WORD_SIZE, obs );

      puts(" ");
      prompt_c( "Enter the name of the first target body: ", 
                                                   WORD_SIZE, targ1 );

      puts(" ");
      prompt_c( "Enter the name of the second target body: ", 
                                                   WORD_SIZE, targ2 );

      /*
      Get the beginning and ending UTC times for the time interval
      of interest.
      */
      puts(" ");
      prompt_c ( "Enter the beginning UTC time: ", WORD_SIZE, utcbeg );

      puts(" ");
      prompt_c ( "Enter the ending UTC time: ",    WORD_SIZE, utcend );

      puts (" ");
      puts ("Working ... Please wait.");
      puts (" ");


      /*
      Convert the UTC times to ephemeris seconds past J2000 (ET),
      since that is what the SPICELIB readers are expecting.
      */
      str2et_c ( utcbeg, &etbeg );
      str2et_c ( utcend, &etend );
      et2utc_c ( etbeg, "C", 0, WORD_SIZE, utcbeg );
      et2utc_c ( etend, "C", 0, WORD_SIZE, utcend );

      /*
      Calculate the difference between evaluation times.
      */
      delta  = ( etend - etbeg ) / ( (SpiceDouble) MAXPTS  - 1.);

      /*
      For each time, get the apparent states of the two target
      bodies as seen from the observer.
      */
      et = etbeg;

      for ( i=0; i < MAXPTS; ++i )
         {
         /*
         Compute the state of targ1 and targ2 from obs at et then
         calculate the angular separation between targ1 and targ2 
         as seen from obs. Convert that angular value from radians 
         to degrees.
         */
         spkezr_c (  targ1, et, ref, corr, obs, state1, &lt1 );
         spkezr_c (  targ2, et, ref, corr, obs, state2, &lt2 );
 
         /*
         Save the time and the separation between the target bodies
         (in degrees), as seen from the observer, for output to the
         screen.
         */
         x[i] = et;
         y[i] = vsep_c ( state1, state2) * dpr_c();
         et   = et + delta;
         }

      /*
      Display the time and angular separation of the desired
      target bodies for the requested observer for each of the
      equally spaced evaluation times in the given time interval.

      If you have a graphics package, you may wish to write the
      time and angular separation data to a file, and then plot
      them for added effect.
      */
      puts( " ");
      printf( "The angular separation between bodies %s and %s,\n",
                                                    targ1, targ2 );
      printf( "as seen from body %s.\n", obs );
 
      puts( " ");
      printf( "From: %s\n", utcbeg ); 
      printf( "To  : %s\n", utcend );

      puts (" ");
      puts ("       UTC Time                 Separation" );
      puts ("----------------------------------------------");

      for ( i = 0; i < MAXPTS; ++i )
         {
         et2utc_c ( x[i], "C", 0, WORD_SIZE, utctim );
         printf ( "  %.20s     %15.8f deg\n", utctim, y[i] );
         }

      puts( " " );
      prompt_c ( "Continue? (Enter Y or N): ", WORD_SIZE, answer );
      puts( " " );
      puts( " " );
         
      /*
      Perform a logical test to see if the user wants to
      continue.
      */
      if ( eqstr_c( "N", answer) )
         {
         cont = SPICEFALSE;
         }

      }
   while ( cont == SPICETRUE );


   return ( 0 );
   }
