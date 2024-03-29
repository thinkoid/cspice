/* dlatdr.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure DLATDR ( Derivative of latitudinal w.r.t. rectangular ) */
/* Subroutine */ int dlatdr_(doublereal *x, doublereal *y, doublereal *z__, 
	doublereal *jacobi)
{
    doublereal long__, r__;
    extern /* Subroutine */ int chkin_(char *, ftnlen), vpack_(doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    doublereal injacb[9]	/* was [3][3] */;
    extern /* Subroutine */ int reclat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    doublereal rectan[3];
    extern /* Subroutine */ int drdlat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), sigerr_(char *, ftnlen), chkout_(
	    char *, ftnlen), setmsg_(char *, ftnlen);
    extern logical return_(void);
    extern /* Subroutine */ int invort_(doublereal *, doublereal *);
    doublereal lat;

/* $ Abstract */

/*     Compute the Jacobian matrix of the transformation from */
/*     rectangular to latitudinal coordinates. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     None. */

/* $ Keywords */

/*     COORDINATES */
/*     DERIVATIVES */
/*     MATRIX */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     X          I   X-coordinate of point. */
/*     Y          I   Y-coordinate of point. */
/*     Z          I   Z-coordinate of point. */
/*     JACOBI     O   Matrix of partial derivatives. */

/* $ Detailed_Input */

/*     X, */
/*     Y, */
/*     Z        are the rectangular coordinates of the point at */
/*              which the Jacobian of the map from rectangular */
/*              to latitudinal coordinates is desired. */

/* $ Detailed_Output */

/*     JACOBI   is the matrix of partial derivatives of the conversion */
/*              between rectangular and latitudinal coordinates. It */
/*              has the form */

/*                  .-                              -. */
/*                  |  dr/dx     dr/dy     dr/dz     | */
/*                  |  dlong/dx  dlong/dy  dlong/dz  | */
/*                  |  dlat/dx   dlat/dy   dlat/dz   | */
/*                  `-                              -' */

/*               evaluated at the input values of X, Y, and Z. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If the input point is on the z-axis (X = 0 and Y = 0), the */
/*         Jacobian is undefined, the error SPICE(POINTONZAXIS) is */
/*         signaled. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     When performing vector calculations with velocities it is */
/*     usually most convenient to work in rectangular coordinates. */
/*     However, once the vector manipulations have been performed */
/*     it is often desirable to convert the rectangular representations */
/*     into latitudinal coordinates to gain insights about phenomena */
/*     in this coordinate frame. */

/*     To transform rectangular velocities to derivatives of coordinates */
/*     in a latitudinal system, one uses the Jacobian of the */
/*     transformation between the two systems. */

/*     Given a state in rectangular coordinates */

/*          ( x, y, z, dx, dy, dz ) */

/*     the corresponding latitudinal coordinate derivatives are given by */
/*     the matrix equation: */

/*                         t          |                     t */
/*        (dr, dlong, dlat)   = JACOBI|        * (dx, dy, dz) */
/*                                    |(x,y,z) */

/*     This routine computes the matrix */

/*              | */
/*        JACOBI| */
/*              |(x, y, z) */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */

/*     1) Find the latitudinal state of the Earth as seen from */
/*        Mars in the IAU_MARS reference frame at January 1, 2005 TDB. */
/*        Map this state back to rectangular coordinates as a check. */

/*        Use the meta-kernel shown below to load the required SPICE */
/*        kernels. */


/*           KPL/MK */

/*           File name: dlatdr_ex1.tm */

/*           This meta-kernel is intended to support operation of SPICE */
/*           example programs. The kernels shown here should not be */
/*           assumed to contain adequate or correct versions of data */
/*           required by SPICE-based user applications. */

/*           In order for an application to use this meta-kernel, the */
/*           kernels referenced here must be present in the user's */
/*           current working directory. */

/*           The names and contents of the kernels referenced */
/*           by this meta-kernel are as follows: */

/*              File name                     Contents */
/*              ---------                     -------- */
/*              de421.bsp                     Planetary ephemeris */
/*              pck00010.tpc                  Planet orientation and */
/*                                            radii */
/*              naif0009.tls                  Leapseconds */


/*           \begindata */

/*              KERNELS_TO_LOAD = ( 'de421.bsp', */
/*                                  'pck00010.tpc', */
/*                                  'naif0009.tls'  ) */

/*           \begintext */

/*           End of meta-kernel */


/*        Example code begins here. */


/*              PROGRAM DLATDR_EX1 */
/*              IMPLICIT NONE */

/*        C */
/*        C     SPICELIB functions */
/*        C */
/*              DOUBLE PRECISION      RPD */

/*        C */
/*        C     Local parameters */
/*        C */
/*              CHARACTER*(*)         FMT1 */
/*              PARAMETER           ( FMT1 = '(A,E18.8)' ) */
/*        C */
/*        C     Local variables */
/*        C */
/*              DOUBLE PRECISION      DRECTN ( 3 ) */
/*              DOUBLE PRECISION      ET */
/*              DOUBLE PRECISION      JACOBI ( 3, 3 ) */
/*              DOUBLE PRECISION      LAT */
/*              DOUBLE PRECISION      LON */
/*              DOUBLE PRECISION      LT */
/*              DOUBLE PRECISION      LATVEL ( 3 ) */
/*              DOUBLE PRECISION      RECTAN ( 3 ) */
/*              DOUBLE PRECISION      R */
/*              DOUBLE PRECISION      STATE  ( 6 ) */

/*        C */
/*        C     Load SPK, PCK and LSK kernels, use a meta kernel for */
/*        C     convenience. */
/*        C */
/*              CALL FURNSH ( 'dlatdr_ex1.tm' ) */

/*        C */
/*        C     Look up the apparent state of earth as seen from Mars */
/*        C     at January 1, 2005 TDB, relative to the IAU_MARS */
/*        C     reference frame. */
/*        C */
/*              CALL STR2ET ( 'January 1, 2005 TDB', ET ) */

/*              CALL SPKEZR ( 'Earth', ET,    'IAU_MARS', 'LT+S', */
/*             .              'Mars',  STATE, LT                ) */

/*        C */
/*        C     Convert position to latitudinal coordinates. */
/*        C */
/*              CALL RECLAT ( STATE, R, LON, LAT ) */

/*        C */
/*        C     Convert velocity to latitudinal coordinates. */
/*        C */

/*              CALL DLATDR ( STATE(1), STATE(2), STATE(3), JACOBI ) */

/*              CALL MXV ( JACOBI, STATE(4), LATVEL ) */

/*        C */
/*        C     As a check, convert the latitudinal state back to */
/*        C     rectangular coordinates. */
/*        C */
/*              CALL LATREC ( R, LON, LAT, RECTAN ) */

/*              CALL DRDLAT ( R, LON, LAT, JACOBI ) */

/*              CALL MXV ( JACOBI, LATVEL, DRECTN ) */


/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Rectangular coordinates:' */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,FMT1) '  X (km)                 = ', STATE(1) */
/*              WRITE(*,FMT1) '  Y (km)                 = ', STATE(2) */
/*              WRITE(*,FMT1) '  Z (km)                 = ', STATE(3) */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Rectangular velocity:' */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,FMT1) '  dX/dt (km/s)           = ', STATE(4) */
/*              WRITE(*,FMT1) '  dY/dt (km/s)           = ', STATE(5) */
/*              WRITE(*,FMT1) '  dZ/dt (km/s)           = ', STATE(6) */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Latitudinal coordinates:' */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,FMT1) '  Radius    (km)         = ', R */
/*              WRITE(*,FMT1) '  Longitude (deg)        = ', LON/RPD() */
/*              WRITE(*,FMT1) '  Latitude  (deg)        = ', LAT/RPD() */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Latitudinal velocity:' */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,FMT1) '  d Radius/dt    (km/s)  = ', LATVEL(1) */
/*              WRITE(*,FMT1) '  d Longitude/dt (deg/s) = ', */
/*             .                                         LATVEL(2)/RPD() */
/*              WRITE(*,FMT1) '  d Latitude/dt  (deg/s) = ', */
/*             .                                         LATVEL(3)/RPD() */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Rectangular coordinates from inverse ' // */
/*             .           'mapping:' */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,FMT1) '  X (km)                 = ', RECTAN(1) */
/*              WRITE(*,FMT1) '  Y (km)                 = ', RECTAN(2) */
/*              WRITE(*,FMT1) '  Z (km)                 = ', RECTAN(3) */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Rectangular velocity from inverse mapping:' */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,FMT1) '  dX/dt (km/s)           = ', DRECTN(1) */
/*              WRITE(*,FMT1) '  dY/dt (km/s)           = ', DRECTN(2) */
/*              WRITE(*,FMT1) '  dZ/dt (km/s)           = ', DRECTN(3) */
/*              WRITE(*,*) ' ' */
/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, the output was: */


/*         Rectangular coordinates: */

/*          X (km)                 =    -0.76096183E+08 */
/*          Y (km)                 =     0.32436380E+09 */
/*          Z (km)                 =     0.47470484E+08 */

/*         Rectangular velocity: */

/*          dX/dt (km/s)           =     0.22952075E+05 */
/*          dY/dt (km/s)           =     0.53760111E+04 */
/*          dZ/dt (km/s)           =    -0.20881149E+02 */

/*         Latitudinal coordinates: */

/*          Radius    (km)         =     0.33653522E+09 */
/*          Longitude (deg)        =     0.10320290E+03 */
/*          Latitude  (deg)        =     0.81089866E+01 */

/*         Latitudinal velocity: */

/*          d Radius/dt    (km/s)  =    -0.11211601E+02 */
/*          d Longitude/dt (deg/s) =    -0.40539288E-02 */
/*          d Latitude/dt  (deg/s) =    -0.33189930E-05 */

/*         Rectangular coordinates from inverse mapping: */

/*          X (km)                 =    -0.76096183E+08 */
/*          Y (km)                 =     0.32436380E+09 */
/*          Z (km)                 =     0.47470484E+08 */

/*         Rectangular velocity from inverse mapping: */

/*          dX/dt (km/s)           =     0.22952075E+05 */
/*          dY/dt (km/s)           =     0.53760111E+04 */
/*          dZ/dt (km/s)           =    -0.20881149E+02 */


/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     J. Diaz del Rio    (ODC Space) */
/*     W.L. Taber         (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.1, 26-OCT-2021 (JDR) */

/*        Edited the header to comply with NAIF standard. */
/*        Added complete code example. */

/* -    SPICELIB Version 1.0.0, 16-JUL-2001 (WLT) */

/* -& */
/* $ Index_Entries */

/*     Jacobian of latitudinal w.r.t. rectangular coordinates */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("DLATDR", (ftnlen)6);
    }

/*     There is a singularity of the Jacobian for points on the z-axis. */

    if (*x == 0. && *y == 0.) {
	setmsg_("The Jacobian of the transformation from rectangular to lati"
		"tudinal coordinates is not defined for points on the z-axis.",
		 (ftnlen)119);
	sigerr_("SPICE(POINTONZAXIS)", (ftnlen)19);
	chkout_("DLATDR", (ftnlen)6);
	return 0;
    }

/*     We will get the Jacobian of the transformation from rectangular */
/*     to latitudinal coordinates by implicit differentiation. */

/*     First move the X,Y and Z coordinates into a vector. */

    vpack_(x, y, z__, rectan);

/*     Convert from rectangular to latitudinal coordinates. */

    reclat_(rectan, &r__, &long__, &lat);

/*     Get the Jacobian of the transformation from latitudinal to */
/*     rectangular coordinates at R, LONG, LAT. */

    drdlat_(&r__, &long__, &lat, injacb);

/*     Now invert INJACB to get the Jacobian of the transformation from */
/*     rectangular to latitudinal coordinates. */

    invort_(injacb, jacobi);
    chkout_("DLATDR", (ftnlen)6);
    return 0;
} /* dlatdr_ */

