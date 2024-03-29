/* param.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* Table of constant values */

static integer c__10 = 10;
static integer c__1 = 1;

/* $Procedure      PARAM ( Process a SUBTeX parameter item ) */
/* Subroutine */ int param_(char *source, integer *n, ftnlen source_len)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen), s_rnge(char *, integer, 
	    char *, integer);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    char line[132];
    integer i__, l, begin;
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    char names[132*10];
    extern /* Subroutine */ int tempb_(char *, char *, ftnlen, ftnlen);
    integer pgwid, width;
    char token[132];
    integer lskip, nskip, rskip, nsize;
    extern /* Subroutine */ int ljust_(char *, char *, ftnlen, ftnlen), 
	    clearc_(integer *, char *, ftnlen);
    integer nl, nn, beginn, remain, indent;
    extern /* Subroutine */ int params_(char *, char *, integer *, ftnlen, 
	    ftnlen), chkout_(char *, ftnlen), tokens_(char *, char *, integer 
	    *, char *, integer *, ftnlen, ftnlen, ftnlen), suffix_(char *, 
	    integer *, char *, ftnlen, ftnlen);
    extern logical return_(void);
    extern integer pos_(char *, char *, integer *, ftnlen, ftnlen);

/* $ Abstract */

/*     Process a @param or @moreparam control sequence. */

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

/*     SUBTeX */

/* $ Keywords */

/*     SUBTeX */

/* $ Declarations */
/* $ Detailed_Input */

/*     SOURCE      are the source lines containing a @param control */
/*                 sequence, followed by a parameter name and */
/*                 explanatory paragraph; or containing @moreparam */
/*                 and a paragraph. */

/*     N           is the number of source lines. */

/* $ Detailed_Output */

/*     Processed lines are saved in the temporary buffer. */

/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     SOURCE     I   Source lines. */
/*     N          I   Number of source lines. */

/* $ Files */

/*     None. */

/* $ Exceptions */

/*     None. */

/* $ Particulars */


/* $ Examples */


/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/* $Include SUBTeX.REFS */

/* $ Author_and_Institution */

/*     I.M. Underwood (JPL) */

/* $ Version */

/*     Beta Version 1.0.0, 11-JUN-1988 (IMU) */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling */

    if (return_()) {
	return 0;
    } else {
	chkin_("PARAM", (ftnlen)5);
    }

/*     Retrieve the required parameters. */

    params_("GET", "PAGEWIDTH", &width, (ftnlen)3, (ftnlen)9);
    params_("GET", "LEFTSKIP", &lskip, (ftnlen)3, (ftnlen)8);
    params_("GET", "RIGHTSKIP", &rskip, (ftnlen)3, (ftnlen)9);
    params_("GET", "ITEMINDENT", &indent, (ftnlen)3, (ftnlen)10);
    params_("GET", "PARAMNAMESIZE", &nsize, (ftnlen)3, (ftnlen)13);
    params_("GET", "PARAMNAMESKIP", &nskip, (ftnlen)3, (ftnlen)13);

/*     The first token should be @param. */

    tokens_("NEW", source, n, token, &l, (ftnlen)3, source_len, (ftnlen)132);

/*     The next set of tokens (up to a delimiting period) is the */
/*     set of variable names. Begin a new one every time a carriage */
/*     return (@cr) is encountered. Store up to 10. */

    clearc_(&c__10, names, (ftnlen)132);
    nn = 1;
    if (s_cmp(token, "@param", (ftnlen)132, (ftnlen)6) == 0) {
	tokens_("NEXT", source, n, token, &l, (ftnlen)4, source_len, (ftnlen)
		132);
	while(pos_(token, ".", &c__1, (ftnlen)132, (ftnlen)1) == 0) {
	    if (s_cmp(token, "@cr", (ftnlen)132, (ftnlen)3) == 0) {
		++nn;
	    } else if (nn <= 10) {
		suffix_(token, &c__1, names + ((i__1 = nn - 1) < 10 && 0 <= 
			i__1 ? i__1 : s_rnge("names", i__1, "param_", (ftnlen)
			175)) * 132, (ftnlen)132, (ftnlen)132);
	    }
	    tokens_("NEXT", source, n, token, &l, (ftnlen)4, source_len, (
		    ftnlen)132);
	}
	if (s_cmp(token, ".", (ftnlen)132, (ftnlen)1) != 0 && s_cmp(token, 
		"@cr.", (ftnlen)132, (ftnlen)4) != 0 && nn < 10) {
	    i__ = pos_(token, ".", &c__1, (ftnlen)132, (ftnlen)1) - 1;
	    suffix_(token, &c__1, names + ((i__1 = nn - 1) < 10 && 0 <= i__1 ?
		     i__1 : s_rnge("names", i__1, "param_", (ftnlen)186)) * 
		    132, i__, (ftnlen)132);
	}
    }

/*     The rest of the text is reformatted into a paragraph of width */

/*        PAGEWIDTH - LEFTSKIP */
/*                  - RIGHTSKIP */
/*                  - ITEMINDENT */
/*                  - PARAMNAMESIZE */
/*                  - PARAMNAMESKIP */

/*     beginning in column */

/*        LEFTSKIP + ITEMINDENT + PARAMNAMESIZE + PARAMTYPESKIP + 1 */

/*     Keep grabbing tokens until they run out. Start a new line whenever */
/*     the current line becomes full. REMAIN is the number of spaces */
/*     remaining in the current line. */

/*     Names begin in column */

/*        LEFTSKIP + ITEMINDENT + 1 */

/*     until they run out. */

    pgwid = width - lskip - rskip - indent - nsize - nskip;
    begin = lskip + indent + nsize + nskip + 1;
    beginn = lskip + indent + 1;
    remain = pgwid;
    nl = 1;
    s_copy(line, " ", (ftnlen)132, (ftnlen)1);
    s_copy(token, " ", (ftnlen)132, (ftnlen)1);
    tokens_("NEXT", source, n, token, &l, (ftnlen)4, source_len, pgwid);
    while(s_cmp(token, " ", (ftnlen)132, (ftnlen)1) != 0) {
	if (l > remain || s_cmp(token, "@newline", (ftnlen)132, (ftnlen)8) == 
		0) {
	    if (nl <= nn) {
		ljust_(names + ((i__1 = nl - 1) < 10 && 0 <= i__1 ? i__1 : 
			s_rnge("names", i__1, "param_", (ftnlen)235)) * 132, 
			line + (beginn - 1), (ftnlen)132, beginn + nsize - 1 
			- (beginn - 1));
	    }
	    tempb_("ADD", line, (ftnlen)3, (ftnlen)132);
	    ++nl;
	    s_copy(line, " ", (ftnlen)132, (ftnlen)1);
	    remain = pgwid;
	    s_copy(line + (begin - 1), token, 132 - (begin - 1), (ftnlen)132);
	    remain = remain - l - 1;
	} else if (s_cmp(line + (begin - 1), " ", 132 - (begin - 1), (ftnlen)
		1) == 0) {
	    s_copy(line + (begin - 1), token, 132 - (begin - 1), (ftnlen)132);
	    remain = remain - l - 1;
	} else {
	    suffix_(token, &c__1, line + (begin - 1), (ftnlen)132, 132 - (
		    begin - 1));
	    remain = remain - l - 1;
	}
	tokens_("NEXT", source, n, token, &l, (ftnlen)4, source_len, pgwid);
    }
    if (s_cmp(line, " ", (ftnlen)132, (ftnlen)1) != 0) {
	if (nl <= nn) {
	    ljust_(names + ((i__1 = nl - 1) < 10 && 0 <= i__1 ? i__1 : s_rnge(
		    "names", i__1, "param_", (ftnlen)260)) * 132, line + (
		    beginn - 1), (ftnlen)132, beginn + nsize - 1 - (beginn - 
		    1));
	}
	tempb_("ADD", line, (ftnlen)3, (ftnlen)132);
	++nl;
    }

/*     There may, in fact, be more lines of names than lines */
/*     of text. */

    i__1 = nn;
    for (i__ = nl; i__ <= i__1; ++i__) {
	s_copy(line, " ", (ftnlen)132, (ftnlen)1);
	if (i__ <= nn) {
	    ljust_(names + ((i__2 = i__ - 1) < 10 && 0 <= i__2 ? i__2 : 
		    s_rnge("names", i__2, "param_", (ftnlen)276)) * 132, line 
		    + (beginn - 1), (ftnlen)132, beginn + nsize - 1 - (beginn 
		    - 1));
	}
	tempb_("ADD", line, (ftnlen)3, (ftnlen)132);
	s_copy(line, " ", (ftnlen)132, (ftnlen)1);
    }

/*     Every parameter item is followed by a blank line. */

    tempb_("ADD", " ", (ftnlen)3, (ftnlen)1);
    chkout_("PARAM", (ftnlen)5);
    return 0;
} /* param_ */

