/* saelgv.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* Table of constant values */

static integer c__3 = 3;

/* $Procedure SAELGV ( Semi-axes of ellipse from generating vectors ) */
/* Subroutine */ int saelgv_(doublereal *vec1, doublereal *vec2, doublereal *
	smajor, doublereal *sminor)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_rnge(char *, integer, char *, integer);

    /* Local variables */
    extern doublereal vdot_(doublereal *, doublereal *);
    doublereal c__[4]	/* was [2][2] */;
    integer i__;
    doublereal s[4]	/* was [2][2] */, scale;
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    integer major;
    extern /* Subroutine */ int moved_(doublereal *, integer *, doublereal *),
	     vlcom_(doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    integer minor;
    extern doublereal vnorm_(doublereal *);
    extern /* Subroutine */ int diags2_(doublereal *, doublereal *, 
	    doublereal *);
    doublereal tmpvc1[3], tmpvc2[3];
    extern /* Subroutine */ int cleard_(integer *, doublereal *);
    doublereal eigval[4]	/* was [2][2] */;
    extern /* Subroutine */ int chkout_(char *, ftnlen), vsclip_(doublereal *,
	     doublereal *);
    extern logical return_(void);

/* $ Abstract */

/*     Find semi-axis vectors of an ellipse generated by two arbitrary */
/*     three-dimensional vectors. */

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

/*     ELLIPSES */

/* $ Keywords */

/*     ELLIPSE */
/*     GEOMETRY */
/*     MATH */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     VEC1, */
/*     VEC2       I   Two vectors used to generate an ellipse. */
/*     SMAJOR     O   Semi-major axis of ellipse. */
/*     SMINOR     O   Semi-minor axis of ellipse. */

/* $ Detailed_Input */

/*     VEC1, */
/*     VEC2     are two vectors that define an ellipse. */
/*              The ellipse is the set of points in 3-space */

/*                 CENTER  +  cos(theta) VEC1  +  sin(theta) VEC2 */

/*              where theta is in the interval ( -pi, pi ] and */
/*              CENTER is an arbitrary point at which the ellipse */
/*              is centered. An ellipse's semi-axes are */
/*              independent of its center, so the vector CENTER */
/*              shown above is not an input to this routine. */

/*              VEC2 and VEC1 need not be linearly independent; */
/*              degenerate input ellipses are allowed. */

/* $ Detailed_Output */

/*     SMAJOR, */
/*     SMINOR   are semi-major and semi-minor axes of the ellipse, */
/*              respectively. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If one or more semi-axes of the ellipse is found to be the */
/*         zero vector, the input ellipse is degenerate. This case is */
/*         not treated as an error; the calling program must determine */
/*         whether the semi-axes are suitable for the program's intended */
/*         use. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     Two linearly independent but not necessarily orthogonal vectors */
/*     VEC1 and VEC2 can define an ellipse centered at the origin: the */
/*     ellipse is the set of points in 3-space */

/*        CENTER  +  cos(theta) VEC1  +  sin(theta) VEC2 */

/*     where theta is in the interval (-pi, pi] and CENTER is an */
/*     arbitrary point at which the ellipse is centered. */

/*     This routine finds vectors that constitute semi-axes of an */
/*     ellipse that is defined, except for the location of its center, */
/*     by VEC1 and VEC2. The semi-major axis is a vector of largest */
/*     possible magnitude in the set */

/*        cos(theta) VEC1  +  sin(theta) VEC2 */

/*     There are two such vectors; they are additive inverses of each */
/*     other. The semi-minor axis is an analogous vector of smallest */
/*     possible magnitude. The semi-major and semi-minor axes are */
/*     orthogonal to each other. If SMAJOR and SMINOR are choices of */
/*     semi-major and semi-minor axes, then the input ellipse can also */
/*     be represented as the set of points */

/*        CENTER  +  cos(theta) SMAJOR  +  sin(theta) SMINOR */

/*     where theta is in the interval (-pi, pi]. */

/*     The capability of finding the axes of an ellipse is useful in */
/*     finding the image of an ellipse under a linear transformation. */
/*     Finding this image is useful for determining the orthogonal and */
/*     gnomonic projections of an ellipse, and also for finding the limb */
/*     and terminator of an ellipsoidal body. */

/* $ Examples */

/*     1)  An example using inputs that can be readily checked by */
/*         hand calculation. */

/*            Let */

/*               VEC1 = ( 1.D0,  1.D0,  1.D0 ) */
/*               VEC2 = ( 1.D0, -1.D0,  1.D0 ) */

/*           The subroutine call */

/*              CALL SAELGV ( VEC1, VEC2, SMAJOR, SMINOR ) */

/*           returns */

/*              SMAJOR = ( -1.414213562373095D0, */
/*                          0.0D0, */
/*                         -1.414213562373095D0 ) */
/*           and */

/*              SMINOR = ( -2.4037033579794549D-17 */
/*                          1.414213562373095D0, */
/*                         -2.4037033579794549D-17 ) */


/*     2)   This example is taken from the code of the SPICELIB routine */
/*          PJELPL, which finds the orthogonal projection of an ellipse */
/*          onto a plane. The code listed below is the portion used to */
/*          find the semi-axes of the projected ellipse. */

/*             C */
/*             C     Project vectors defining axes of ellipse onto plane. */
/*             C */
/*                   CALL VPERP ( VEC1,   NORMAL,  PROJ1  ) */
/*                   CALL VPERP ( VEC2,   NORMAL,  PROJ2  ) */

/*                      . */
/*                      . */
/*                      . */

/*                   CALL SAELGV ( PROJ1,  PROJ2,  SMAJOR,  SMINOR ) */


/*          The call to SAELGV determines the required semi-axes. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     [1]  T. Apostol, "Calculus, Vol. II," chapter 5, "Eigenvalues of */
/*          Operators Acting on Euclidean Spaces," John Wiley & Sons, */
/*          1969. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     J. Diaz del Rio    (ODC Space) */
/*     W.L. Taber         (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.2.0, 28-MAY-2021 (JDR) */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. */

/* -    SPICELIB Version 1.1.1, 22-APR-2010 (NJB) */

/*        Header correction: assertions that the output */
/*        can overwrite the input have been removed. */

/* -    SPICELIB Version 1.1.0, 02-SEP-2005 (NJB) */

/*        Updated to remove non-standard use of duplicate arguments */
/*        in VSCL calls. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 02-NOV-1990 (NJB) (WLT) */

/* -& */
/* $ Index_Entries */

/*     semi-axes of ellipse from generating vectors */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("SAELGV", (ftnlen)6);
    }

/*        Let the notation */

/*           < a, b > */

/*        indicate the inner product of the vectors a and b. */

/*        The semi-major and semi-minor axes of the input ellipse are */
/*        vectors of maximum and minimum norm in the set */

/*           cos(x) VEC1  +  sin(x) VEC2 */

/*        where x is in the interval (-pi, pi]. */

/*        The square of the norm of a vector in this set is */

/*                                                2 */
/*               || cos(x) VEC1  +  sin(x) VEC2 || */


/*           =   < cos(x)VEC1 + sin(x)VEC2,  cos(x)VEC1 + sin(x)VEC2 > ; */

/*        this last expression can be written as the matrix product */

/*            T */
/*           X  S  X,                                                 (1) */

/*        where X is the unit vector */

/*           +-      -+ */
/*           | cos(x) | */
/*           |        | */
/*           | sin(x) | */
/*           +-      -+ */

/*        and S is the symmetric matrix */

/*           +-                                -+ */
/*           | < VEC1, VEC1 >    < VEC1, VEC2 > | */
/*           |                                  |. */
/*           | < VEC1, VEC2 >    < VEC2, VEC2 > | */
/*           +-                                -+ */

/*        Because the 2x2 matrix above is symmetric, there exists a */
/*        rotation matrix that allows us to diagonalize it: */

/*            T */
/*           C  S  C  =  D, */

/*        where D is a diagonal matrix.  Since rotation matrices are */
/*        orthogonal, we have */

/*            T */
/*           C  C  =  I. */

/*        If the unit vector U is defined by */

/*                T */
/*           U = C X, */

/*        then */

/*            T             T  T         T               T */
/*           X  S  X  =  ( U  C  )  C D C   ( C U )  =  U  D  U. */

/*        So, letting */

/*           +-   -+ */
/*           |  u  | */
/*           |     |  =  U, */
/*           |  v  | */
/*           +-   -+ */

/*        we may re-write the original quadratic expression (1) as */

/*           +-     -+    +-        -+    +-   -+ */
/*           | u   v |    | D1    0  |    |  u  |, */
/*           +-     -+    |          |    |     | */
/*                        |          |    |  v  | */
/*                        | 0     D2 |    +-   -+ */
/*                        +-        -+ */
/*        or */

/*               2            2 */
/*           D1 u    +    D2 v, */

/*        where the diagonal matrix above is D.  The eigenvalues D1 and */
/*        D2 are non-negative because they are eigenvalues of a positive */
/*        semi-definite matrix of the form */

/*            T */
/*           M  M. */

/*        We may require that */

/*           D1  >  D2; */
/*               - */

/*        then the maximum and minimum values of */

/*               2            2 */
/*           D1 u    +    D2 v                                        (2) */

/*        are D1 and D2 respectively.  These values are the squares */
/*        of the lengths of the semi-major and semi-minor axes of the */
/*        ellipse, since the expression (2) is the square of the norm */
/*        of the point */

/*           cos(x) VEC1  + sin(x) VEC2. */

/*        Now we must find some eigenvectors.  Since the extrema of (2) */
/*        occur when */

/*                +-   -+                     +-   -+ */
/*                |  1  |                     |  0  | */
/*           U =  |     |       or       U =  |     |, */
/*                |  0  |                     |  1  | */
/*                +-   -+                     +-   -+ */

/*        and since */

/*           X = C U, */

/*        we conclude that the extrema occur when X = C1 or X = C2, where */
/*        C1 and C2 are the first and second columns of C.  Looking at */
/*        the definition of X, we see that the extrema occur when */

/*           cos(x) = C1(1) */
/*           sin(x) = C1(2) */

/*        and when */

/*           cos(x) = C2(1), */
/*           sin(x) = C2(2) */

/*        So the semi-major and semi-minor axes of the ellipse are */

/*           C(1,1) VEC1  +  C(2,1) VEC2 */

/*        and */

/*           C(1,2) VEC1  +  C(2,2) VEC2 */

/*        (the negatives of these vectors are also semi-axes). */


/*     Copy the input vectors. */

    moved_(vec1, &c__3, tmpvc1);
    moved_(vec2, &c__3, tmpvc2);

/*     Scale the vectors to try to prevent arithmetic unpleasantness. */
/*     We avoid using the quotient 1/SCALE, as this value may overflow. */
/*     No need to go further if SCALE turns out to be zero. */

/* Computing MAX */
    d__1 = vnorm_(tmpvc1), d__2 = vnorm_(tmpvc2);
    scale = max(d__1,d__2);
    if (scale == 0.) {
	cleard_(&c__3, smajor);
	cleard_(&c__3, sminor);
	chkout_("SAELGV", (ftnlen)6);
	return 0;
    }
    for (i__ = 1; i__ <= 3; ++i__) {
	tmpvc1[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("tmpvc1", 
		i__1, "saelgv_", (ftnlen)435)] = tmpvc1[(i__2 = i__ - 1) < 3 
		&& 0 <= i__2 ? i__2 : s_rnge("tmpvc1", i__2, "saelgv_", (
		ftnlen)435)] / scale;
	tmpvc2[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("tmpvc2", 
		i__1, "saelgv_", (ftnlen)436)] = tmpvc2[(i__2 = i__ - 1) < 3 
		&& 0 <= i__2 ? i__2 : s_rnge("tmpvc2", i__2, "saelgv_", (
		ftnlen)436)] / scale;
    }

/*     Compute S and diagonalize it: */

    s[0] = vdot_(tmpvc1, tmpvc1);
    s[1] = vdot_(tmpvc1, tmpvc2);
    s[2] = s[1];
    s[3] = vdot_(tmpvc2, tmpvc2);
    diags2_(s, eigval, c__);

/*     Find the semi-axes. */

    if (abs(eigval[0]) >= abs(eigval[3])) {

/*        The first eigenvector ( first column of C ) corresponds */
/*        to the semi-major axis of the ellipse. */

	major = 1;
	minor = 2;
    } else {

/*        The second eigenvector corresponds to the semi-major axis. */

	major = 2;
	minor = 1;
    }
    vlcom_(&c__[(i__1 = (major << 1) - 2) < 4 && 0 <= i__1 ? i__1 : s_rnge(
	    "c", i__1, "saelgv_", (ftnlen)469)], tmpvc1, &c__[(i__2 = (major 
	    << 1) - 1) < 4 && 0 <= i__2 ? i__2 : s_rnge("c", i__2, "saelgv_", 
	    (ftnlen)469)], tmpvc2, smajor);
    vlcom_(&c__[(i__1 = (minor << 1) - 2) < 4 && 0 <= i__1 ? i__1 : s_rnge(
	    "c", i__1, "saelgv_", (ftnlen)470)], tmpvc1, &c__[(i__2 = (minor 
	    << 1) - 1) < 4 && 0 <= i__2 ? i__2 : s_rnge("c", i__2, "saelgv_", 
	    (ftnlen)470)], tmpvc2, sminor);

/*     Undo the initial scaling. */

    vsclip_(&scale, smajor);
    vsclip_(&scale, sminor);
    chkout_("SAELGV", (ftnlen)6);
    return 0;
} /* saelgv_ */

