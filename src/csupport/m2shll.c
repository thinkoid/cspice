/* m2shll.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* $Procedure      M2SHLL ( Shell sort an array of Meta/2 syntaxs ) */
/* Subroutine */ int m2shll_(integer *ndim, char *array, ftnlen array_len)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    logical l_le(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    logical swap;
    integer i__, j, k;
    extern /* Subroutine */ int swapc_(char *, char *, ftnlen, ftnlen);
    integer ej, jg, kg, ejg, gap;
    extern integer pos_(char *, char *, integer *, ftnlen, ftnlen);

/* $ Abstract */

/*      Sort an array of character strings according suitable for */
/*      use with META/2. */

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

/*      ARRAY,  SORT */

/* $ Declarations */
/* $ Brief_I/O */

/*      VARIABLE  I/O  DESCRIPTION */
/*      --------  ---  -------------------------------------------------- */
/*      NDIM       I   Dimension of the array. */
/*      ARRAY     I/O  The array of syntax statements */

/* $ Detailed_Input */

/*      NDIM        is the number of elements in the array to be sorted. */

/*      ARRAY       on input, is the array of syntax statements */
/*                  to be sorted. */

/* $ Detailed_Output */

/*      ARRAY       on output, contains the same elements, sorted */
/*                  by initial keyword minus any keyword labels. */

/* $ Parameters */

/*     None. */

/* $ Particulars */

/*      The Shell Sort Algorithm is well known. */

/* $ Examples */

/*      Let ARRAY contain the following elements: */

/*            'FEYNMAN' */
/*            'NEWTON' */
/*            'EINSTEIN' */
/*            'GALILEO' */
/*            'EUCLID' */
/*            'Galileo' */

/*      Then after a call to M2SHLL, the array would be ordered as */
/*      follows: */

/*            'EINSTEIN' */
/*            'EUCLID' */
/*            'FEYNMAN' */
/*            'GALILEO' */
/*            'Galileo' */
/*            'NEWTON' */

/* $ Restrictions */

/*      None. */

/* $ Exceptions */

/*      Error free. */

/* $ Files */

/*      None. */

/* $ Author_and_Institution */

/*      I.M. Underwood  (JPL) */

/* $ Literature_References */

/*      None. */

/* $ Version */

/* -     Meta/2  Version 1.0.0, 4-SEP-1998 (WLT) */

/*         Modified SHELLC to produce an initial keyword sort. */

/* -     SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*         Comment section for permuted index source lines was added */
/*         following the header. */

/* -     SPICELIB Version 1.0.0, 31-JAN-1990 (IMU) */

/* -& */
/* $ Index_Entries */

/*     shell sort a character array */

/* -& */

/*     SPICELIB Functions */


/*     Local variables */


/*     This is a straightforward implementation of the Shell Sort */
/*     algorithm. */

    gap = *ndim / 2;
    while(gap > 0) {
	i__1 = *ndim;
	for (i__ = gap + 1; i__ <= i__1; ++i__) {
	    j = i__ - gap;
	    while(j > 0) {
		jg = j + gap;
		k = j;
		kg = jg;
		ej = pos_(array + (j - 1) * array_len, "[", &c__1, array_len, 
			(ftnlen)1);
		ejg = pos_(array + (jg - 1) * array_len, "[", &c__1, 
			array_len, (ftnlen)1);
		if (ej > 1) {
		    *(unsigned char *)&array[(j - 1) * array_len + (ej - 1)] =
			     ' ';
		}
		if (ejg > 1) {
		    *(unsigned char *)&array[(jg - 1) * array_len + (ejg - 1)]
			     = ' ';
		}
		if (l_le(array + (j - 1) * array_len, array + (jg - 1) * 
			array_len, array_len, array_len)) {
		    j = 0;
		    swap = FALSE_;
		} else {
		    swap = TRUE_;
		}
		if (ej > 1) {
		    *(unsigned char *)&array[(k - 1) * array_len + (ej - 1)] =
			     '[';
		}
		if (ejg > 1) {
		    *(unsigned char *)&array[(kg - 1) * array_len + (ejg - 1)]
			     = '[';
		}
		if (swap) {
		    swapc_(array + (j - 1) * array_len, array + (jg - 1) * 
			    array_len, array_len, array_len);
		}
		j -= gap;
	    }
	}
	gap /= 2;
    }
    return 0;
} /* m2shll_ */

