/* getchr.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure      GETCHR ( Prompting for a character string value ) */
/* Subroutine */ int getchr_(char *prmpt, char *value, logical *gotval, 
	logical *error, char *errmsg, ftnlen prmpt_len, ftnlen value_len, 
	ftnlen errmsg_len)
{
    /* Builtin functions */
    integer i_len(char *, ftnlen);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    char line[255];
    extern /* Subroutine */ int chkin_(char *, ftnlen), repmi_(char *, char *,
	     integer *, char *, ftnlen, ftnlen, ftnlen), ljust_(char *, char *
	    , ftnlen, ftnlen);
    integer inpbeg, inpend, length;
    extern integer lastnb_(char *, ftnlen);
    integer inplen;
    extern /* Subroutine */ int chkout_(char *, ftnlen);
    extern integer frstnb_(char *, ftnlen);
    extern logical return_(void);
    extern /* Subroutine */ int prompt_(char *, char *, ftnlen, ftnlen);

/* $ Abstract */

/*     This routine provides a portable means for interactively */
/*     obtaining a character string value. */

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

/*     UTILITY */

/* $ Declarations */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*      PRMPT     I    The prompt to be used for the desired value. */
/*      VALUE     O    Value entered, or unchanged, depending on GOTVAL. */
/*      GOTVAL    O    Flag indicating that a value was entered */
/*      ERROR     O    Flag indicating an error occurred. */
/*      ERRMSG    O    Descriptive error message */

/* $ Detailed_Input */

/*     PRMPT    The prompt to be used for the desired value. */

/* $ Detailed_Output */

/*     VALUE    The new value, if the flag GOTVAL = .TRUE., otherwise */
/*              nothing meaningful. */

/*     GOTVAL   A logical flag indicating that a value has been */
/*              entered. */

/*     ERROR    A logical flag indicating that an input error occurred. */

/*     ERRMSG   A descriptive error message when an error occurs, */
/*              blank otherwise. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     None. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     This routine provides an easy to use portable interface for */
/*     obtaining variable values in an interactive fashion with error */
/*     information. */

/*     This is one in a family of routines, one for each data type: */

/*        GETCHR -- Obtain a character string value */
/*        GETDP  -- Obtain a double precision value */
/*        GETINT -- Obtain an integer value */

/* $ Examples */

/*     The following code fragment for obtaining the date */

/*         CALL GETCHR ( 'Date? ', VALUE, GOTVAL, ERROR, ERRMSG ) */

/*     would display on the terminal screen */

/*        Date? _ */

/*     Type in an appropriate character string value. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     K.R. Gehringer (JPL) */

/* $ Version */

/* -    Beta Version 1.0.0, 29-MAY-1992 (KRG) */

/* -& */
/* $ Index_Entries */

/*      prompt for a character string value */

/* -& */

/*     SPICELIB functions */


/*     Local parameters */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("GETCHR", (ftnlen)6);
    }

/*     Set the initial values */

    length = i_len(value, value_len);
    *gotval = FALSE_;
    s_copy(errmsg, " ", errmsg_len, (ftnlen)1);

/*     Get the new value */

    if (s_cmp(prmpt, " ", prmpt_len, (ftnlen)1) != 0) {
	prompt_(prmpt, line, prmpt_len, (ftnlen)255);
    } else {
	prompt_("Value: ", line, (ftnlen)7, (ftnlen)255);
    }
    ljust_(line, line, (ftnlen)255, (ftnlen)255);
    if (s_cmp(line, " ", (ftnlen)255, (ftnlen)1) != 0) {
	inpbeg = frstnb_(line, (ftnlen)255);
	inpend = lastnb_(line, (ftnlen)255);
	inplen = inpend - inpbeg + 1;
	if (length >= inplen) {
	    s_copy(value, line + (inpbeg - 1), value_len, inpend - (inpbeg - 
		    1));
	    *gotval = TRUE_;
	} else {
	    *error = TRUE_;
	    s_copy(errmsg, "ERROR: Input string was too long, only # charact"
		    "ers are allowed.", errmsg_len, (ftnlen)64);
	    repmi_(errmsg, "#", &length, errmsg, errmsg_len, (ftnlen)1, 
		    errmsg_len);
	}
    }
    chkout_("GETCHR", (ftnlen)6);
    return 0;
} /* getchr_ */

