/*

-Procedure sphlat_c ( Spherical to latitudinal coordinates )

-Abstract

   Convert from spherical coordinates to latitudinal coordinates.

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

   CONVERSION
   COORDINATES

*/

   #include <cspice/SpiceUsr.h>


   void sphlat_c ( SpiceDouble     r,
                   SpiceDouble     colat,
                   SpiceDouble     slon,
                   SpiceDouble   * radius,
                   SpiceDouble   * lon,
                   SpiceDouble   * lat )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   r          I   Distance of the point from the origin.
   colat      I   Angle of the point from positive z axis (radians).
   slon       I   Angle of the point from the XZ plane (radians).
   radius     O   Distance of a point from the origin
   lon        O   Angle of the point from the XZ plane in radians
   lat        O   Angle of the point from the XY plane in radians

-Detailed_Input

   r           is the distance of the point from the origin.

   colat       is the angle between the vector from the origin to the
               point and the positive Z-axis in radians.

   slon        is the angle of the point from the XZ plane (radians).

-Detailed_Output

   radius      is the distance of a point from the origin.

   lon         is the angle of the point from the XZ plane in
               radians. `lon' is set equal to `slon'.

   lat         is the angle of the point from the XY plane in
               radians. `lat' is computed as pi/2 - colat.

-Parameters

   None.

-Exceptions

   Error free.

-Files

   None.

-Particulars

   This routine returns the latitudinal coordinates of a point
   whose position is input in spherical coordinates.

   Latitudinal coordinates are defined by a distance from a central
   reference point, an angle from a reference meridian, and an angle
   above the equator of a sphere centered at the central reference
   point.

   Spherical coordinates are defined by a distance from a central
   reference point, an angle from a reference meridian, and an angle
   from the z-axis.

-Examples

   The numerical results shown for these examples may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) Latitude is obtained by subtracting co-latitude from halfpi_c
      Radius and longitude mean the same thing in both latitudinal
      and spherical coordinates. The table below lists `lat' and
      corresponding `colat' in terms of degrees.

           lat     colat
          -----    -----
             0        90
            20        70
            45        45
           -30       120
            90         0
           -45       135


   2) Compute the spherical coordinates of the position of the Moon
      as seen from the Earth, and convert them to latitudinal and
      rectangular coordinates.

      Use the meta-kernel shown below to load the required SPICE
      kernels.


         KPL/MK

         File name: sphlat_ex2.tm

         This meta-kernel is intended to support operation of SPICE
         example programs. The kernels shown here should not be
         assumed to contain adequate or correct versions of data
         required by SPICE-based user applications.

         In order for an application to use this meta-kernel, the
         kernels referenced here must be present in the user's
         current working directory.

         The names and contents of the kernels referenced
         by this meta-kernel are as follows:

            File name                     Contents
            ---------                     --------
            de421.bsp                     Planetary ephemeris
            naif0012.tls                  Leapseconds


         \begindata

            KERNELS_TO_LOAD = ( 'de421.bsp',
                                'naif0012.tls'  )

         \begintext

         End of meta-kernel


      Example code begins here.


      /.
         Program sphlat_ex2
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {

         /.
         Local variables
         ./
         SpiceDouble          colat;
         SpiceDouble          et;
         SpiceDouble          lt;
         SpiceDouble          lat;
         SpiceDouble          lon;
         SpiceDouble          pos    [3];
         SpiceDouble          r;
         SpiceDouble          radius;
         SpiceDouble          rectan [3];
         SpiceDouble          slon;

         /.
         Load SPK and LSK kernels, use a meta kernel for
         convenience.
         ./
         furnsh_c ( "sphlat_ex2.tm" );

         /.
         Look up the geometric state of the Moon as seen from
         the Earth at 2017 Mar 20, relative to the J2000
         reference frame.
         ./
         str2et_c ( "2017 Mar 20", &et );

         spkpos_c ( "Moon", et, "J2000", "NONE", "Earth", pos, &lt );

         /.
         Convert the position vector `pos' to spherical
         coordinates.
         ./
         recsph_c ( pos, &r, &colat, &slon );

         /.
         Convert the spherical coordinates to latitudinal.
         ./
         sphlat_c ( r, colat, slon, &radius, &lon, &lat );

         /.
         Convert the latitudinal coordinates to rectangular.
         ./
         latrec_c ( radius, lon, lat, rectan );

         printf( " \n" );
         printf( "Original rectangular coordinates:\n" );
         printf( " \n" );
         printf( " X           (km):  %19.8f\n", pos[0] );
         printf( " Y           (km):  %19.8f\n", pos[1] );
         printf( " Z           (km):  %19.8f\n", pos[2] );
         printf( " \n" );
         printf( "Spherical coordinates:\n" );
         printf( " \n" );
         printf( " Radius      (km):  %19.8f\n", r );
         printf( " Colatitude (deg):  %19.8f\n", colat*dpr_c ( ) );
         printf( " Longitude  (deg):  %19.8f\n", slon*dpr_c ( ) );
         printf( " \n" );
         printf( "Latitudinal coordinates:\n" );
         printf( " \n" );
         printf( " Radius      (km):  %19.8f\n", radius );
         printf( " Longitude  (deg):  %19.8f\n", lon*dpr_c ( ) );
         printf( " Latitude   (deg):  %19.8f\n", lat*dpr_c ( ) );
         printf( " \n" );
         printf( "Rectangular coordinates from latrec_c:\n" );
         printf( " \n" );
         printf( " X           (km):  %19.8f\n", rectan[0] );
         printf( " Y           (km):  %19.8f\n", rectan[1] );
         printf( " Z           (km):  %19.8f\n", rectan[2] );
         printf( " \n" );

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Original rectangular coordinates:

       X           (km):      -55658.44323296
       Y           (km):     -379226.32931475
       Z           (km):     -126505.93063865

      Spherical coordinates:

       Radius      (km):      403626.33912495
       Colatitude (deg):         108.26566077
       Longitude  (deg):         -98.34959789

      Latitudinal coordinates:

       Radius      (km):      403626.33912495
       Longitude  (deg):         -98.34959789
       Latitude   (deg):         -18.26566077

      Rectangular coordinates from latrec_c:

       X           (km):      -55658.44323296
       Y           (km):     -379226.32931475
       Z           (km):     -126505.93063865


   3) Create a table showing a variety of spherical coordinates
      and the corresponding cylindrical coordinates.

      Corresponding spherical and cylindrical coordinates are
      listed to three decimal places. Input and output angles
      are in degrees.


      Example code begins here.


      /.
         Program sphlat_ex3
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {

         /.
         Local parameters.
         ./
         #define NREC         11

         /.
         Local variables.
         ./
         SpiceDouble          lat;
         SpiceDouble          lon;
         SpiceDouble          radius;
         SpiceDouble          rcolat;
         SpiceDouble          rslon;

         SpiceInt             i;

         /.
         Define the input spherical coordinates. Angles in degrees.
         ./
         SpiceDouble          r      [NREC] = {  0.0,  1.0,     1.0,
                                                 1.0,  1.4142,  1.0,
                                                 1.0,  1.0,     1.4142,
                                                 1.0,  0.0             };

         SpiceDouble          colat  [NREC] = {  0.0,  90.0,  90.0,
                                                 0.0,  45.0,  90.0,
                                               180.0,  90.0, 135.0,
                                                 0.0,  90.0        };

         SpiceDouble          slon   [NREC] = {  0.0,   0.0,  90.0,
                                                 0.0, 180.0, -90.0,
                                                 0.0,  45.0, 180.0,
                                               180.0,  33.0        };

         /.
         Print the banner.
         ./
         printf( "    r      colat     slon    radius    lon      lat\n"   );
         printf( " -------  -------  -------  -------  -------  -------\n" );

         /.
         Do the conversion. Output angles in degrees.
         ./
         for ( i = 0; i < NREC; i++ )
         {

            rcolat = colat[i] * rpd_c ( );
            rslon  = slon[i]  * rpd_c ( );

            sphlat_c ( r[i], rcolat, rslon, &radius, &lon, &lat );

            printf( "%8.3f %8.3f %8.3f ", r[i], colat[i], slon[i] );
            printf( "%8.3f %8.3f %8.3f\n", radius, lon * dpr_c ( ),
                                                   lat * dpr_c ( ) );

         }

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


          r      colat     slon    radius    lon      lat
       -------  -------  -------  -------  -------  -------
         0.000    0.000    0.000    0.000    0.000   90.000
         1.000   90.000    0.000    1.000    0.000    0.000
         1.000   90.000   90.000    1.000   90.000    0.000
         1.000    0.000    0.000    1.000    0.000   90.000
         1.414   45.000  180.000    1.414  180.000   45.000
         1.000   90.000  -90.000    1.000  -90.000    0.000
         1.000  180.000    0.000    1.000    0.000  -90.000
         1.000   90.000   45.000    1.000   45.000    0.000
         1.414  135.000  180.000    1.414  180.000  -45.000
         1.000    0.000  180.000    1.000  180.000   90.000
         0.000   90.000   33.000    0.000   33.000    0.000


-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   J. Diaz del Rio     (ODC Space)
   B.V. Semenov        (JPL)
   W.L. Taber          (JPL)
   E.D. Wright         (JPL)

-Version

   -CSPICE Version 1.1.0, 05-JUL-2021 (JDR)

       Changed the output argument name "lons" to "slon" for
       consistency with other routines.

       Edited the header to comply with NAIF standard.
       Added complete code examples.

   -CSPICE Version 1.0.1, 26-JUL-2016 (BVS)

       Minor headers edits.

   -CSPICE Version 1.0.0, 08-FEB-1998 (EDW) (WLT)

-Index_Entries

   spherical to latitudinal coordinates

-&
*/

{ /* Begin sphlat_c */

   /*
   Local variables
   */

   SpiceDouble    rr;
   SpiceDouble    lattud;

   rr     = r;
   lattud = halfpi_c() - colat;


   /* Move the results to the output variables. */

   *lon    = slon;
   *radius = rr;
   *lat    = lattud;


} /* End sphlat_c */
