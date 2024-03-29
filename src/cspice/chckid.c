/* chckid.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure CHCKID ( Check ID string ) */
/* Subroutine */ int chckid_(char *class__, integer *maxlen, char *id, ftnlen 
	class_len, ftnlen id_len)
{
    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    integer i__, l;
    extern /* Subroutine */ int chkin_(char *, ftnlen), errch_(char *, char *,
	     ftnlen, ftnlen);
    integer chrcod;
    extern integer lastnb_(char *, ftnlen);
    extern /* Subroutine */ int sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen), setmsg_(char *, ftnlen), errint_(char *, integer *, 
	    ftnlen);
    extern integer frstnp_(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Validate an ID string: check for non-printing characters */
/*     or excessive non-blank length. */

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

/*     STRING */
/*     UTILITY */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     CLASS      I   A description of the class to which ID belongs. */
/*     MAXLEN     I   Maximum allowed non-blank length of ID. */
/*     ID         I   The ID string to be validated. */

/* $ Detailed_Input */

/*     CLASS    is a descriptive string indicating the type of */
/*              object represented by ID. Examples are */
/*              'SPK segment identifier', 'DAF internal file name', */
/*              or 'EK table name'. */

/*              If the input ID is found to be invalid, CLASS is */
/*              used in the error message generated by this */
/*              routine. */

/*     MAXLEN   is the maximum allowed non-blank length of the */
/*              input ID string. If ID has any non-blank */
/*              characters at positions greater than MAXLEN, */
/*              an error will be signaled. */

/*     ID       is the input ID string to be checked. In order */
/*              to be considered valid, ID must contain only */
/*              printing characters and must satisfy the condition */

/*                 LASTNB( ID )  <  MAXLEN */
/*                               - */

/* $ Detailed_Output */

/*     None. See $Particulars for a description of the effect of this */
/*     routine. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If ID contains any nonprintable characters, the error */
/*         SPICE(NONPRINTABLECHARS) is signaled. */

/*     2)  If MAXLEN is non-positive, the error SPICE(INVALIDCOUNT) is */
/*          signaled. */

/*     3)  If ID contains any non-blank characters past position */
/*         MAXLEN, the error SPICE(IDSTRINGTOOLONG) is signaled. */

/*     4)  If CLASS contains any non-printing characters, the error */
/*         SPICE(NONPRINTABLECHARS) is signaled. */

/*     5)  CLASS is allowed to be blank. The word 'ID' is used in */
/*         place of the class string in any error messages in this */
/*         case. */

/*     6)  The error messages output by this routine have a maximum */
/*         length of 320 characters. If substitution of CLASS and */
/*         ID into the long messages causes overflow, the messages */
/*         will be truncated on the right. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     This routine operates by side effects: it validates an ID string */
/*     and signals an error if the ID has either of the following */
/*     problems: */

/*     -  There are non-printing characters in the ID string. */

/*     -  The last non-blank character in the string occurs at a */
/*        location having index higher than a specified value. */

/*     The error message signaled by this routine contains the offending */
/*     ID string and indicates the class of item to which ID belongs. */
/*     The form of the message is: */

/*         The <CLASS> <'ID'> is invalid; <reason> */

/* $ Examples */

/*     1)  If */

/*            CLASS  = 'segment identifier' */
/*            MAXLEN =  40 */

/*         and */

/*            ID = 'Example EK created on March 28, 1995 by NJB/NAIF' */

/*         the error message */

/*            The segment identifier 'Example EK created on March 28, */
/*            1995 by NJB/NAIF' is invalid; the last non-blank character */
/*            is located at position 48. */

/*         will be signaled. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     J. Diaz del Rio    (ODC Space) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 02-JUN-2021 (JDR) */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. */

/* -    SPICELIB Version 1.0.0, 16-JUN-1995 (NJB) */

/* -& */
/* $ Index_Entries */

/*     check an ID string */
/*     validate an ID string */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("CHCKID", (ftnlen)6);
    }

/*     Check CLASS before trying to use it in an error message. */

    i__ = frstnp_(class__, class_len);
    if (i__ > 0) {
	chrcod = *(unsigned char *)&class__[i__ - 1];
	setmsg_("The class string '#' is invalid; this string contains a non"
		"-printing character (ICHAR = #) at position #.", (ftnlen)105);
	errch_("#", class__, (ftnlen)1, class_len);
	errint_("#", &chrcod, (ftnlen)1);
	errint_("#", &i__, (ftnlen)1);
	sigerr_("SPICE(NONPRINTABLECHARS)", (ftnlen)24);
	chkout_("CHCKID", (ftnlen)6);
	return 0;
    }

/*     MAXLEN must be a sensible value. */

    if (*maxlen < 1) {
	setmsg_("Non-blank length limit MAXLEN should be positive but was #.",
		 (ftnlen)59);
	errint_("#", maxlen, (ftnlen)1);
	sigerr_("SPICE(INVALIDCOUNT)", (ftnlen)19);
	chkout_("CHCKID", (ftnlen)6);
	return 0;
    }
    l = lastnb_(id, id_len);

/*     The ID must not be too long. */

    if (l > *maxlen) {
	setmsg_("The # '#' is invalid; the last non-blank character is locat"
		"ed at position #; the maximum allowed length is #.", (ftnlen)
		109);
	if (s_cmp(class__, " ", class_len, (ftnlen)1) != 0) {
	    errch_("#", class__, (ftnlen)1, class_len);
	} else {
	    errch_("#", "ID", (ftnlen)1, (ftnlen)2);
	}
	errch_("#", id, (ftnlen)1, id_len);
	errint_("#", &l, (ftnlen)1);
	errint_("#", maxlen, (ftnlen)1);
	sigerr_("SPICE(IDSTRINGTOOLONG)", (ftnlen)22);
	chkout_("CHCKID", (ftnlen)6);
	return 0;
    }

/*     Look for non-printing characters in ID. */

    i__ = frstnp_(id, id_len);
    if (i__ > 0) {
	chrcod = *(unsigned char *)&id[i__ - 1];
	setmsg_("The # '#' is invalid; this string contains a non-printing c"
		"haracter (ICHAR = #) at position #.", (ftnlen)94);
	if (s_cmp(class__, " ", class_len, (ftnlen)1) != 0) {
	    errch_("#", class__, (ftnlen)1, class_len);
	} else {
	    errch_("#", "ID", (ftnlen)1, (ftnlen)2);
	}
	errch_("#", id, (ftnlen)1, id_len);
	errint_("#", &chrcod, (ftnlen)1);
	errint_("#", &i__, (ftnlen)1);
	sigerr_("SPICE(NONPRINTABLECHARS)", (ftnlen)24);
	chkout_("CHCKID", (ftnlen)6);
	return 0;
    }
    chkout_("CHCKID", (ftnlen)6);
    return 0;
} /* chckid_ */

