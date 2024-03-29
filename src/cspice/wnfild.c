/* wnfild.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure WNFILD ( Fill small gaps in a DP window ) */
/* Subroutine */ int wnfild_(doublereal *smlgap, doublereal *window)
{
    integer card, i__, j;
    extern integer cardd_(doublereal *);
    extern /* Subroutine */ int chkin_(char *, ftnlen), scardd_(integer *, 
	    doublereal *), chkout_(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Fill small gaps between adjacent intervals of a double precision */
/*     window. */

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

/*     WINDOWS */

/* $ Keywords */

/*     WINDOWS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     SMLGAP     I   Limiting measure of small gaps. */
/*     WINDOW    I-O  Window to be filled. */

/* $ Detailed_Input */

/*     SMLGAP   is the limiting measure of the small gaps to be filled. */
/*              Adjacent intervals separated by gaps of measure less than */
/*              or equal to SMLGAP are merged. The measure SMLGAP is */
/*              signed, and is used as is---the absolute value of SMLGAP */
/*              is not used for in place of negative input values. */

/*     WINDOW   on input, is a window containing zero or more */
/*              intervals. */

/* $ Detailed_Output */

/*     WINDOW   on output, is the original window, after adjacent */
/*              intervals separated by small gaps have been merged. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  The cardinality of the input WINDOW must be even. Left */
/*         endpoints of stored intervals must be strictly greater than */
/*         preceding right endpoints. Right endpoints must be greater */
/*         than or equal to corresponding left endpoints. Invalid window */
/*         data are not diagnosed by this routine and may lead to */
/*         unpredictable results. */

/*     2)  If SMLGAP is less than or equal to zero, this routine has */
/*         no effect on the window. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     This routine removes small gaps between adjacent intervals */
/*     by merging intervals separated by gaps of measure less than */
/*     or equal to the limiting measure SMLGAP. */

/* $ Examples */

/*     The numerical results shown for these examples may differ across */
/*     platforms. The results depend on the SPICE kernels used as input, */
/*     the compiler and supporting libraries, and the machine specific */
/*     arithmetic implementation. */

/*     1) Given a double precision window, containing the following four */
/*        intervals: */

/*           [ 1.0, 3.0 ], [ 7.0, 11.0 ], [ 23.0, 27.0 ], [ 29.0, 29.0 ] */

/*        merge any adjacent intervals separated by a gap equal to or */
/*        less than 3.0. */


/*        Example code begins here. */


/*              PROGRAM WNFILD_EX1 */
/*              IMPLICIT NONE */

/*        C */
/*        C     SPICELIB functions */
/*        C */
/*              INTEGER               WNCARD */

/*        C */
/*        C     Local parameters. */
/*        C */
/*              CHARACTER*(*)         FMT */
/*              PARAMETER           ( FMT    = '(A,I2,A,2(F7.3,A))' ) */

/*              INTEGER               LBCELL */
/*              PARAMETER           ( LBCELL = -5 ) */

/*              INTEGER               WNSIZE */
/*              PARAMETER           ( WNSIZE = 10 ) */

/*        C */
/*        C     Local variables. */
/*        C */
/*              DOUBLE PRECISION      LEFT */
/*              DOUBLE PRECISION      RIGHT */
/*              DOUBLE PRECISION      WINDOW ( LBCELL:WNSIZE ) */

/*              INTEGER               I */

/*        C */
/*        C     Validate the WINDOW with size WNSIZE and zero elements. */
/*        C */
/*              CALL WNVALD ( WNSIZE, 0, WINDOW ) */

/*        C */
/*        C     Insert the intervals */
/*        C */
/*        C        [ 1, 3 ]  [ 7, 11 ]  [ 23, 27 ]  [ 29, 29 ] */
/*        C */
/*        C     into WINDOW. */
/*        C */
/*              CALL WNINSD ( 1.0D0,  3.0D0,  WINDOW ) */
/*              CALL WNINSD ( 7.0D0,  11.0D0, WINDOW ) */
/*              CALL WNINSD ( 23.0D0, 27.0D0, WINDOW ) */
/*              CALL WNINSD ( 29.0D0, 29.0D0, WINDOW ) */

/*        C */
/*        C     Loop over the number of intervals in WINDOW, output */
/*        C     the LEFT and RIGHT endpoints for each interval. */
/*        C */
/*              WRITE(*,*) 'Initial WINDOW:' */

/*              DO I= 1, WNCARD( WINDOW ) */

/*                 CALL WNFETD ( WINDOW, I, LEFT, RIGHT ) */

/*                 WRITE(*,FMT) '   Interval ', I, ': [', */
/*             .                LEFT, ',', RIGHT, ' ]' */

/*              END DO */

/*        C */
/*        C     Fill the gaps smaller than or equal to 3.0 */
/*        C */
/*              CALL WNFILD ( 3.0D0, WINDOW ) */

/*        C */
/*        C     Output the intervals. */
/*        C */
/*              WRITE(*,*) ' ' */
/*              WRITE(*,*) 'Window after filling gaps <= 3.0:' */

/*              DO I= 1, WNCARD( WINDOW ) */

/*                 CALL WNFETD ( WINDOW, I, LEFT, RIGHT ) */

/*                 WRITE(*,FMT) '   Interval ', I, ': [', */
/*             .                LEFT, ',', RIGHT, ' ]' */

/*              END DO */

/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, the output was: */


/*         Initial WINDOW: */
/*           Interval  1: [  1.000,  3.000 ] */
/*           Interval  2: [  7.000, 11.000 ] */
/*           Interval  3: [ 23.000, 27.000 ] */
/*           Interval  4: [ 29.000, 29.000 ] */

/*         Window after filling gaps <= 3.0: */
/*           Interval  1: [  1.000,  3.000 ] */
/*           Interval  2: [  7.000, 11.000 ] */
/*           Interval  3: [ 23.000, 29.000 ] */


/*     2) Using the same window from the first example: */

/*           [ 1.0, 3.0 ], [ 7.0, 11.0 ], [ 23.0, 27.0 ], [ 29.0, 29.0 ] */

/*        Then the following series of calls */

/*           CALL WNFILD (  1.D0, WINDOW )                           (1) */
/*           CALL WNFILD (  2.D0, WINDOW )                           (2) */
/*           CALL WNFILD (  3.D0, WINDOW )                           (3) */
/*           CALL WNFILD ( 12.D0, WINDOW )                           (4) */

/*        produces the following series of windows */

/*           [1.0,  3.0]  [7.0, 11.0]  [23.0, 27.0]  [29.0, 29.0]    (1) */
/*           [1.0,  3.0]  [7.0, 11.0]  [23.0, 29.0]                  (2) */
/*           [1.0,  3.0]  [7.0, 11.0]  [23.0, 29.0]                  (3) */
/*           [1.0, 29.0]                                             (4) */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     J. Diaz del Rio    (ODC Space) */
/*     H.A. Neilan        (JPL) */
/*     W.L. Taber         (JPL) */
/*     I.M. Underwood     (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 05-JUL-2021 (JDR) (NJB) */

/*        Changed the argument name SMALL to SMLGAP for consistency with */
/*        other routines. */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. Removed */
/*        unnecessary $Revisions section. */

/*        Added complete code example. Added entry #1 and #2 in */
/*        $Exceptions section. Extended SMLGAP description in */
/*        $Detailed_Input. */

/*        Updated code to remove unnecessary lines of code in the */
/*        Standard SPICE error handling CHKIN statements. */

/* -    SPICELIB Version 1.0.3, 29-JUL-2007 (NJB) */

/*        Corrected typo in the previous Version line date string, */
/*        "29-JUL-20022" to "29-JUL-2002." */

/* -    SPICELIB Version 1.0.2, 29-JUL-2002 (NJB) */

/*        Changed gap size from 10 to 12 to correct erroneous example. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (WLT) (IMU) (HAN) */

/* -& */
/* $ Index_Entries */

/*     fill small gaps in a d.p. window */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    }
    chkin_("WNFILD", (ftnlen)6);

/*     Get the cardinality of the window. (The size is not important; */
/*     this routine can't create any new intervals.) */

    card = cardd_(window);

/*     Step through the window, looking for the next right endpoint */
/*     more than SMLGAP away from the following left endpoint. This marks */
/*     the end of the new first interval, and the beginning of the new */
/*     second interval. Keep this up until the last right endpoint has */
/*     been reached. This remains the last right endpoint. */

    if (card > 0) {
	i__ = 2;
	j = 2;
	while(j < card) {
	    if (window[j + 5] + *smlgap < window[j + 6]) {
		window[i__ + 5] = window[j + 5];
		window[i__ + 6] = window[j + 6];
		i__ += 2;
	    }
	    j += 2;
	}
	window[i__ + 5] = window[j + 5];
	scardd_(&i__, window);
    }
    chkout_("WNFILD", (ftnlen)6);
    return 0;
} /* wnfild_ */

