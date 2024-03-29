/* sizecb_1.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure SIZECB ( Size of character buffer ) */
integer sizecb_1__(char *buffer, ftnlen buffer_len)
{
    /* System generated locals */
    integer ret_val;

    /* Builtin functions */
    integer i_len(char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int chkin_(char *, ftnlen), chkout_(char *, 
	    ftnlen);
    extern integer dimcb_1__(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Return the total size of a character buffer. */

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

/*     CB */

/* $ Keywords */

/*     ASCII */
/*     CHARACTER */
/*     STRING */
/*     TEXT */

/* $ Declarations */
/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     BUFFER     I   Character buffer. */

/* $ Detailed_Input */

/*     BUFFER      is a character buffer. */

/* $ Detailed_Output */

/*     The function returns the total size of the character buffer */
/*     (as established by a previous call to CBINIT). This is the */
/*     total number of characters that can be stored in the buffer. */

/* $ Files */

/*     None. */

/* $ Exceptions */

/*     None. */

/* $ Particulars */

/*     The size of a character buffer is checked before any operation */
/*     is performed on the buffer, to detect possible overflows. */

/* $ Examples */

/*     The code fragment */

/*        INTEGER            LBCBUF */
/*        PARAMETER        ( LBCBUF = 0 ) */

/*        INTEGER            DIMCB */
/*        INTEGER            SIZECB */
/*        CHARACTER*100      BUFFER  ( LBCBUF:200 ) */

/*        CALL CBINIT ( 200, BUFFER ) */

/*        WRITE (*,*) DIMCB  ( BUFFER ),    ' elements at ' */
/*        WRITE (*,*) LEN    ( BUFFER(1) ), ' characters each totals ' */
/*        WRITE (*,*) SIZECB ( BUFFER ),    ' characters of storage.' */

/*     produces the following output. */

/*        200    elements at */
/*        100    characters each totals */
/*        200000 characters of storage. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     Dagny Taggart, (JPL) */

/* $ Version */

/* -    Beta Version 1.1.0, 28-DEC-1994 (WLT) */

/*        The function is assigned an initial value of 0 so that it */
/*        will have some value if we are in RETURN mode. */

/* -    Beta Version 1.0.0, 19-JAN-1989 (DT) */

/* -& */

/*     SPICELIB functions */


/*     Give the function some initial value.  Zero seems as good as */
/*     anything. */

    ret_val = 0;

/*     Standard error handling. */

    if (return_()) {
	return ret_val;
    } else {
	chkin_("SIZECB_1", (ftnlen)8);
    }

/*     Size = dimension * length. */

    ret_val = dimcb_1__(buffer, buffer_len) * i_len(buffer + buffer_len, 
	    buffer_len);
    chkout_("SIZECB_1", (ftnlen)8);
    return ret_val;
} /* sizecb_1__ */

