/* vsub.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure VSUB ( Vector subtraction, 3 dimensions ) */
/* Subroutine */ int vsub_(doublereal *v1, doublereal *v2, doublereal *vout)
{
/* $ Abstract */

/*     Compute the difference between two double precision 3-dimensional */
/*     vectors. */

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

/*     VECTOR */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     V1         I   First vector (minuend). */
/*     V2         I   Second vector (subtrahend). */
/*     VOUT       O   Difference vector, V1 - V2. */

/* $ Detailed_Input */

/*     V1       is a double precision 3-dimensional vector which is the */
/*              minuend (i.e. first or left-hand member) in the vector */
/*              subtraction. */

/*     V2       is a double precision 3-dimensional vector which is the */
/*              subtrahend (i.e. second or right-hand member) in the */
/*              vector subtraction. */

/* $ Detailed_Output */

/*     VOUT     is a double precision 3-dimensional vector which */
/*              represents the vector difference, V1 - V2. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     Error free. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     For each value of the index I from 1 to 3, this routine performs */
/*     the following subtraction: */

/*        VOUT(I) = V1(I) - V2(I) */

/*     No error checking is performed to guard against numeric overflow */
/*     or underflow. */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */

/*     1) Define two sets of 3-dimensional vectors and compute the */
/*        difference from each vector in first set with the */
/*        corresponding vector in the second set. */


/*        Example code begins here. */


/*              PROGRAM VSUB_EX1 */
/*              IMPLICIT NONE */

/*        C */
/*        C     Local parameters. */
/*        C */
/*              INTEGER               SETSIZ */
/*              PARAMETER           ( SETSIZ = 3 ) */

/*        C */
/*        C     Local variables. */
/*        C */
/*              DOUBLE PRECISION      V1   ( 3, SETSIZ ) */
/*              DOUBLE PRECISION      V2   ( 3, SETSIZ ) */
/*              DOUBLE PRECISION      VOUT ( 3         ) */

/*              INTEGER               I */
/*              INTEGER               J */

/*        C */
/*        C     Define the two vector sets. */
/*        C */
/*              DATA                  V1 / 1.D0,  2.D0,  3.D0, */
/*             .                           1.D0,  2.D0,  3.D0, */
/*             .                           1.D0,  2.D0,  3.D0  / */

/*              DATA                  V2 / 1.D0,  1.D0,  1.D0, */
/*             .                          -1.D0, -2.D0, -3.D0, */
/*             .                          -1.D0,  2.D0, -3.D0  / */

/*        C */
/*        C     Calculate the difference between each pair of vectors */
/*        C */
/*              DO I=1, SETSIZ */

/*                 CALL VSUB ( V1(1,I), V2(1,I), VOUT ) */

/*                 WRITE(*,'(A,3F6.1)') 'First vector : ', */
/*             .                        ( V1(J,I), J=1,3 ) */
/*                 WRITE(*,'(A,3F6.1)') 'Second vector: ', */
/*             .                        ( V2(J,I), J=1,3 ) */
/*                 WRITE(*,'(A,3F6.1)') 'Difference   : ', VOUT */
/*                 WRITE(*,*) */

/*              END DO */

/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, the output was: */


/*        First vector :    1.0   2.0   3.0 */
/*        Second vector:    1.0   1.0   1.0 */
/*        Difference   :    0.0   1.0   2.0 */

/*        First vector :    1.0   2.0   3.0 */
/*        Second vector:   -1.0  -2.0  -3.0 */
/*        Difference   :    2.0   4.0   6.0 */

/*        First vector :    1.0   2.0   3.0 */
/*        Second vector:   -1.0   2.0  -3.0 */
/*        Difference   :    2.0   0.0   6.0 */


/* $ Restrictions */

/*     1)  The user is required to determine that the magnitude each */
/*         component of the vectors is within the appropriate range so as */
/*         not to cause floating point overflow. No error recovery or */
/*         reporting scheme is incorporated in this routine. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     J. Diaz del Rio    (ODC Space) */
/*     W.M. Owen          (JPL) */
/*     W.L. Taber         (JPL) */
/*     E.D. Wright        (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.4, 03-JUL-2020 (JDR) */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. Added complete */
/*        code example based on existing example. */

/* -    SPICELIB Version 1.0.3, 22-APR-2010 (NJB) */

/*        Header correction: assertions that the output */
/*        can overwrite the input have been removed. */

/* -    SPICELIB Version 1.0.2, 07-NOV-2003 (EDW) */

/*        Corrected a mistake in the second example's value */
/*        for VOUT, i.e. replaced (1D24, 2D23, 0.0) with */
/*        (-1D24, 0.0, 0.0). */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (WMO) */

/* -& */
/* $ Index_Entries */

/*     3-dimensional vector subtraction */

/* -& */
    vout[0] = v1[0] - v2[0];
    vout[1] = v1[1] - v2[1];
    vout[2] = v1[2] - v2[2];
    return 0;
} /* vsub_ */

