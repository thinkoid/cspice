/*

-Procedure subpt ( Compute a sub-observer point )


-Abstract

   This "cookbook" program demonstrates the use of the CSPICE
   Toolkit by computing the apparent sub-observer point on a target
   body. It uses light time and stellar aberration corrections in
   order to do this.

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

   The user is prompted for the following:

      - The name of a leapseconds kernel file.
      - The name of a Planetary constants (PCK) kernel file.
      - The name of a NAIF SPK Ephemeris file.
      - The name of the observing body.
      - The name of the target body.
      - The name of the body-fixed reference frame
        associated with the target body (for example, IAU_MARS).
      - Number of evaluations to perform
      - A UTC time interval of interest.

-Output

   The program calculates the planetocentric latitude and longitude
   of the nearest point on the target body to the observing body
   for a UTC epoch (see Input above). The program outputs

      - The epoch of interest as supplied by the user.
      - The planetocentric longitude of the nearest point on
        the target body to the observing body.
      - The planetocentric latitude of the nearest point on
        the target body to the observing body.

-Particulars

   The SPK file must contain data for both the observing body and
   the target body during the specified time interval.

   The "apparent sub-observer point" is defined in this program to
   be the point on the target body that appears to be closest to the
   observer. The apparent sub-observer point may also be defined as
   the intercept on the target's surface of the ray emanating from
   the observer and passing through the apparent target body's
   center, but we don't demonstrate use of that definition here. See
   the header of subpnt_c for details.

   In order to compute the apparent location of the sub-observer
   point, we correct the position of the sub-observer point for both
   light time and stellar aberration, and we correct the orientation
   of the target body for light time. We consider "light time" to be
   the time it takes a photon to travel from the sub-observer point
   to the observer. If the light time is given the name LT, then the
   apparent position of the sub-observer point relative to the
   observer is defined by the vector from the sub-observer point's
   location (relative to the solar system barycenter) at ET-LT,
   minus the observer's location (again, relative to the solar
   system barycenter) at ET, where this difference vector is
   corrected for stellar aberration.

   See the header of the CSPICE routine spkezr_c for more
   information on light time and stellar aberration corrections; see
   the header of the CSPICE routine subpnt_c for an explanation of
   how it applies aberration corrections.

   Planetocentric coordinates are defined by a distance from a
   central reference point, an angle from a reference meridian,
   and an angle above the equator of a sphere centered at the
   central reference point. These are the radius, longitude,
   and latitude, respectively.

   The program makes use of the following fundamental CSPICE
   interface routines:

      furnsh_c   ---   makes kernel information available to
                       the user's program.

      str2et_c   ---   converts strings representing time to counts
                       of seconds past the J2000 epoch.

      et2utc_c   ---   converts an ephemeris time J200 to
                       a formatted UTC string.

      prompt_c   ---   interactively prompt a user for a string input

      subpnt_c   ---   calculate the position of the sub-observer point
                       of one body with respect to another

   For the sake of brevity, this program does NO error checking
   on its inputs. Mistakes will cause the program to crash.

-References

      KERNEL        The CSPICE Kernel Pool
      ROTATIONS     Rotations
      SPK           S- and P- Kernel (SPK) Specification
      TIME          Time routines in CSPICE

   For questions about a particular subroutine, refer to its
   header.

-Version

   -CSPICE Version 3.0.0, 08-FEB-2008 (NJB)
 
         References to deprecated routine subpt_c have been
         replaced with references to subpnt_c.
 
         The program now uses both stellar aberration and
         light time corrections. Previously only light
         time corrections were performed.
 
         The program now prompts for the name of the target
         body-fixed reference frame.
 
         The discussion in Particulars has been updated.
 
         Various header typos were corrected.

   -CSPICE Version 2.0.0, 11-NOV-2002   (EDW)

      Modified program to reproduce, as precisely as possible,
      output of the FORTRAN version of the SUBPT cookbook.
      Programing style and brevity are secondary to this goal.

   -CSPICE Version 1.0.1, 04-JAN-2002   (EDW)  

      Removed unneeded variable 'format'.
      
   -CSPICE Version 1.0.0, 17-OCT-1999   (EDW)

-&
*/

   /* Include needed headers. */

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <cspice/SpiceUsr.h>



int main()
   {

   /* Local declarations. */

   #define                 FILE_SIZE  128
   #define                 WORD_SIZE   48

   SpiceDouble             delta;
   SpiceDouble             epoch;
   SpiceDouble             etbeg;
   SpiceDouble             etend;
   SpiceDouble             lat;
   SpiceDouble             lon;
   SpiceDouble             radius;
   SpiceDouble             spoint  [3];
   SpiceDouble             srfvec  [3];
   SpiceDouble             trgepc;

   SpiceChar             * abcorr = "LT+S";
   
   SpiceChar               fixfrm[WORD_SIZE];
   SpiceChar               leap  [FILE_SIZE];
   SpiceChar               obs   [WORD_SIZE];
   SpiceChar               pck   [FILE_SIZE];
   SpiceChar               spk   [FILE_SIZE];
   SpiceChar               targ  [WORD_SIZE];
   SpiceChar               utcbeg[WORD_SIZE];
   SpiceChar               utcend[WORD_SIZE];
   SpiceChar               line  [WORD_SIZE];
   SpiceChar               utcout[WORD_SIZE];
   SpiceChar               answer[WORD_SIZE];
   
   SpiceInt                maxpts;
   SpiceInt                npts;

   SpiceBoolean            cont;


   /* An intro banner. */
   puts ( "  ");
   puts ( "             Welcome to SUBPT"                            );
   puts ( ""                                                         );
   puts ( "This program demonstrates the use of CSPICE in computing" );
   puts ( "the apparent sub-observer point on a target body. The"    );
   puts ( "computations use light time and stellar aberration "      );
   puts ( "corrections."                                             );
   puts ( ""                                                         );


   /*
   Start out by prompting for the names of kernel files.
   Load each kernel as the name is supplied.
   
   Get and load the leapsecond kernel.
   */
   prompt_c ( "Enter the name of leapseconds kernel file: ",  
                                                     FILE_SIZE, leap );
   furnsh_c ( leap );
   puts ( " " );


   /* Get and load the physical constants kernel.  */
   prompt_c ( "Enter the name of a planetary constants kernel: ", 
                                                      FILE_SIZE, pck );
   furnsh_c ( pck );
   puts ( " " );


   /* Get and load the spk kernel.  */
   prompt_c ( "Enter the name of a binary SPK file: ", 
                                                      FILE_SIZE, spk );
   furnsh_c ( spk );

   puts (" ");
   puts ("Working ... Please wait.");
   puts (" ");


   /* Set-up for the user response loop */
   cont = SPICETRUE;

   /* Loop till the user quits. */
   do
      {

      /*
      Get the names/IDs for the two target bodies and the observing
      body.
      */

      prompt_c( "Enter the name for the observing body: ", 
                                                     WORD_SIZE, obs );
      puts(" ");

      prompt_c( "Enter the name for a target body: ", 
                                                   WORD_SIZE, targ  );
      puts(" ");

      prompt_c( "Enter the name of the target body-fixed frame: ", 
                                                  WORD_SIZE, fixfrm  );
      puts(" ");

      prompt_c( "Enter the number of points to calculate: ",
                                                    WORD_SIZE, line );
      prsint_c ( line, &maxpts );
      puts( " " );

      if ( maxpts < 1 )
         {
         maxpts = 1;
         }

      /*
      Input strings for the UTC time interval, or single UTC
      time for a single evaluation.

      DELTA is the increment between consecutive times, if
      needed.
      */


      if ( maxpts == 1 ) 
         {

         /* Request for a single evaluation. No steps - no delta. */

         prompt_c ( "Enter the UTC time: ", WORD_SIZE, utcbeg );
         puts(" ");

         str2et_c ( utcbeg, &etbeg );
         delta = 0.;

         }
      else
         {

         /* Request for a time interval with maxpts evaluations. */

         prompt_c ( "Enter the beginning UTC time: ", WORD_SIZE, utcbeg );
         puts(" ");

         prompt_c ( "Enter the ending UTC time: ",    WORD_SIZE, utcend );
         puts(" ");
 
         /*
         Convert the UTC time interval endpoints to seconds past
         J2000 TDB (Barycentric Dynamical Time). TDB is the time
         system used internally in SPK ephemeris files and high
         level SPICE geometry subroutine interfaces. The name "ET"
         used here stands for "Ephemeris Time." ET and TDB are
         treated as synonyms in SPICE documentation.
         */

         str2et_c ( utcbeg, &etbeg );
         str2et_c ( utcend, &etend );

         delta  = ( etend - etbeg ) / ( (SpiceDouble) maxpts - 1. );

         }


      /* Write the headings for the table of values. */

      puts ( "Planetocentric coordinates for the nearest point" );
      puts ( "on the target body to the observing body (deg)."  );
 
      printf( "Target body: %s          Observing body: %s\n", targ,
                                                               obs  ); 
      puts ( " " );
      puts ("       UTC Time            Lat         Lon");
      puts ("----------------------------------------------");
 
      /* Now, everything is set up for output */
      epoch  = etbeg;
      npts   = 1;

      /* Evaluate for maxpts, quit when the user inputs an N. */
      do
         {

         /*
         Note: subpnt_c can also calculate a "sub-observer point" via
         the intercept of the observer-target vector with the target
         body's surface. The computation "method" argument value for
         that calculation is

            "Intercept: ellipsoid"

         The output sub-observer point `spoint' is expressed in the
         body-fixed reference frame `fixfrm' specified by the user,
         where the orientation of the frame is evaluated at the time
         `trgepc'. `trgepc' is expressed in seconds past J2000 TDB, and
         is equal to et-lt, where `lt' is the light time from the
         sub-observer point to the observer. The output `srfvec' is
         the apparent position of the sub-observer point relative to
         the observer. `srfvec' is also expressed in the reference
         frame `fixfrm'.

         Please see the subpnt_c source file header for further
         information.
         */
        
         subpnt_c ( "Near point: ellipsoid", 
                    targ, epoch,  fixfrm,  abcorr,
                    obs,  spoint, &trgepc, srfvec );

         reclat_c ( spoint, &radius, &lon, &lat );

 
         /*
         Multiply lat and lon by the number of degrees per radian.
         */
         lon = lon * dpr_c ();
         lat = lat * dpr_c ();

 
         /* Convert the current epoch to UTC time for display. */
         et2utc_c ( epoch, "C", 3, WORD_SIZE, utcout );


         /* Display results in a table format: */
         printf ( "  %.20s  %9.5f    %9.5f\n", utcout, lat, lon );
            
         epoch = epoch + delta;
         npts = npts + 1;

         }
      while ( npts <= maxpts );


      /* Continue? */
      puts ( " " );
      prompt_c ( "Continue? (Enter Y or N): ", WORD_SIZE, answer );

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
