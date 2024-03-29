/* repmd.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure REPMD  ( Replace marker with double precision number ) */
/* Subroutine */ int repmd_(char *in, char *marker, doublereal *value, 
	integer *sigdig, char *out, ftnlen in_len, ftnlen marker_len, ftnlen 
	out_len)
{
    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer i_indx(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int zzrepsub_(char *, integer *, integer *, char *
	    , char *, ftnlen, ftnlen, ftnlen), dpstr_(doublereal *, integer *,
	     char *, ftnlen);
    integer mrknbf, subnbf;
    extern integer lastnb_(char *, ftnlen);
    integer mrknbl, subnbl;
    extern integer frstnb_(char *, ftnlen);
    integer mrkpsb, mrkpse;
    char substr[23];

/* $ Abstract */

/*     Replace a marker with a double precision number. */

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

/*     CHARACTER */
/*     CONVERSION */
/*     STRING */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     IN         I   Input string. */
/*     MARKER     I   Marker to be replaced. */
/*     VALUE      I   Replacement value. */
/*     SIGDIG     I   Significant digits in replacement text. */
/*     OUT        O   Output string. */
/*     MAXLDP     P   Maximum length of a DP number. */

/* $ Detailed_Input */

/*     IN       is an arbitrary character string. */

/*     MARKER   is an arbitrary character string. The first occurrence of */
/*              MARKER in the input string is to be replaced by VALUE. */

/*              Leading and trailing blanks in MARKER are NOT */
/*              significant. In particular, no substitution is performed */
/*              if MARKER is blank. */

/*     VALUE    is an arbitrary double precision number. */

/*     SIGDIG   is the number of significant digits with which VALUE is */
/*              to be represented. SIGDIG must be greater than zero and */
/*              less than 15. */

/* $ Detailed_Output */

/*     OUT      is the string obtained by substituting the text */
/*              representation of VALUE for the first occurrence of */
/*              MARKER in the input string. */

/*              The text representation of VALUE is in scientific */
/*              notation, having the number of significant digits */
/*              specified by SIGDIG. The representation of VALUE is */
/*              produced by the SPICELIB routine DPSTR; see that routine */
/*              for details concerning the representation of double */
/*              precision numbers. */

/*              OUT and IN must be identical or disjoint. */

/* $ Parameters */

/*     MAXLDP   is the maximum expected length of the text representation */
/*              of a double precision number. 23 characters are */
/*              sufficient to hold any result returned by the SPICELIB */
/*              routine DPSTR. (See $Restrictions) */

/*              This routine assumes that the input d.p. value is such */
/*              that its string representation contains no more than */
/*              MAXLDP characters. */

/* $ Exceptions */

/*     Error free. */

/*     1)  If OUT does not have sufficient length to accommodate the */
/*         result of the substitution, the result will be truncated on */
/*         the right. */

/*     2)  If MARKER is blank, or if MARKER is not a substring of IN, */
/*         no substitution is performed. (OUT and IN are identical.) */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     This is one of a family of related routines for inserting values */
/*     into strings. They are typically to construct messages that */
/*     are partly fixed, and partly determined at run time. For example, */
/*     a message like */

/*        'Fifty-one pictures were found in directory [USER.DATA].' */

/*     might be constructed from the fixed string */

/*        '#1 pictures were found in directory #2.' */

/*     by the calls */

/*        CALL REPMCT ( STRING, '#1',  51,           'C', STRING ) */
/*        CALL REPMC  ( STRING, '#2', '[USER.DATA]',      STRING ) */

/*     which substitute the cardinal text 'Fifty-one' and the character */
/*     string '[USER.DATA]' for the markers '#1' and '#2' respectively. */

/*     The complete list of routines is shown below. */

/*        REPMC    ( Replace marker with character string value ) */
/*        REPMD    ( Replace marker with double precision value ) */
/*        REPMF    ( Replace marker with formatted d.p. value   ) */
/*        REPMI    ( Replace marker with integer value          ) */
/*        REPML    ( Replace marker with logical value          ) */
/*        REPMCT   ( Replace marker with cardinal text          ) */
/*        REPMOT   ( Replace marker with ordinal text           ) */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */

/*     1) The following example illustrate the use of REPMD to */
/*        replace a marker within a string with the text representation */
/*        of a double precision value. */


/*        Example code begins here. */


/*              PROGRAM REPMD_EX1 */
/*              IMPLICIT NONE */

/*        C */
/*        C     Local parameters. */
/*        C */
/*              INTEGER                 STRLEN */
/*              PARAMETER             ( STRLEN = 80 ) */

/*        C */
/*        C     Local variables. */
/*        C */
/*              CHARACTER*(STRLEN)      INSTR */
/*              CHARACTER*(STRLEN)      MARKER */
/*              CHARACTER*(STRLEN)      OUTSTR */

/*        C */
/*        C     1. Single marker, two significant digits. */
/*        C */
/*              MARKER = '#' */
/*              INSTR  = 'Invalid value. The value was:  #' */

/*              CALL REPMD ( INSTR, MARKER, 5.0D1, 2, OUTSTR ) */

/*              WRITE(*,*) 'Case 1: Single marker, two significant ' */
/*             .        // 'digits.' */
/*              WRITE(*,*) '   Input : ', INSTR */
/*              WRITE(*,*) '   Output: ', OUTSTR */
/*              WRITE(*,*) */

/*        C */
/*        C     2. Multiple markers, three significant digits. */
/*        C */
/*              MARKER = ' XX ' */
/*              INSTR  = 'Left > Right endpoint. Left: XX; Right: XX' */

/*              CALL REPMD ( INSTR, MARKER, -5.2D-9, 3, OUTSTR ) */

/*              WRITE(*,*) 'Case 2: Multiple markers, three ' */
/*             .        // 'significant digits.' */
/*              WRITE(*,*) '   Input : ', INSTR */
/*              WRITE(*,*) '   Output: ', OUTSTR */
/*              WRITE(*,*) */

/*        C */
/*        C     3. Excessive significant digits. */
/*        C */
/*              MARKER = '#' */
/*              INSTR  = 'Invalid value. The value was:  #' */

/*              CALL REPMD ( INSTR, MARKER, 5.0D1, 100, OUTSTR ) */

/*              WRITE(*,*) 'Case 3: Excessive significant digits.' */
/*              WRITE(*,*) '   Input : ', INSTR */
/*              WRITE(*,*) '   Output: ', OUTSTR */
/*              WRITE(*,*) */

/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, the output was: */


/*         Case 1: Single marker, two significant digits. */
/*            Input : Invalid value. The value was:  # */
/*            Output: Invalid value. The value was:  5.0E+01 */

/*         Case 2: Multiple markers, three significant digits. */
/*            Input : Left > Right endpoint. Left: XX; Right: XX */
/*            Output: Left > Right endpoint. Left: -5.20E-09; Right: XX */

/*         Case 3: Excessive significant digits. */
/*            Input : Invalid value. The value was:  # */
/*            Output: Invalid value. The value was:  5.0000000000000E+01 */


/*        Note that, in Case #3 even though 100 digits of precision were */
/*        requested, only 14 were returned. */

/* $ Restrictions */

/*     1)  The maximum number of significant digits returned is 14. */

/*     2)  This routine makes explicit use of the format of the string */
/*         returned by the SPICELIB routine DPSTR; should that routine */
/*         change, substantial work may be required to bring this routine */
/*         back up to snuff. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     J. Diaz del Rio    (ODC Space) */
/*     B.V. Semenov       (JPL) */
/*     W.L. Taber         (JPL) */
/*     I.M. Underwood     (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.3.0, 03-OCT-2021 (JDR) */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. Added complete */
/*        code example based on existing fragments. */

/*        Added REPML to the list of available replace marker routines in */
/*        $Particulars and extended the description of MAXLDP in */
/*        $Parameters. */

/* -    SPICELIB Version 1.2.0, 23-SEP-2013 (BVS) */

/*        Minor efficiency update: the routine now looks up the first */
/*        and last non-blank characters only once. */

/* -    SPICELIB Version 1.1.0, 15-AUG-2002 (WLT) */

/*        The routine is now error free. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 30-AUG-1990 (NJB) (IMU) */

/* -& */
/* $ Index_Entries */

/*     replace marker with d.p. number */

/* -& */

/*     SPICELIB functions */


/*     Local variables */



/*     If MARKER is blank, no substitution is possible. */

    if (s_cmp(marker, " ", marker_len, (ftnlen)1) == 0) {
	s_copy(out, in, out_len, in_len);
	return 0;
    }

/*     Locate the leftmost occurrence of MARKER, if there is one */
/*     (ignoring leading and trailing blanks). If MARKER is not */
/*     a substring of IN, no substitution can be performed. */

    mrknbf = frstnb_(marker, marker_len);
    mrknbl = lastnb_(marker, marker_len);
    mrkpsb = i_indx(in, marker + (mrknbf - 1), in_len, mrknbl - (mrknbf - 1));
    if (mrkpsb == 0) {
	s_copy(out, in, out_len, in_len);
	return 0;
    }
    mrkpse = mrkpsb + mrknbl - mrknbf;

/*     Okay, MARKER is non-blank and has been found. Convert the */
/*     number to text, and substitute the text for the marker. */

    dpstr_(value, sigdig, substr, (ftnlen)23);
    subnbf = frstnb_(substr, (ftnlen)23);
    subnbl = lastnb_(substr, (ftnlen)23);
    if (subnbf != 0 && subnbl != 0) {
	zzrepsub_(in, &mrkpsb, &mrkpse, substr + (subnbf - 1), out, in_len, 
		subnbl - (subnbf - 1), out_len);
    }
    return 0;
} /* repmd_ */

