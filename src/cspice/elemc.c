/* elemc.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure ELEMC ( Element of a character set ) */
logical elemc_(char *item, char *a, ftnlen item_len, ftnlen a_len)
{
    /* System generated locals */
    integer i__1;
    logical ret_val;

    /* Local variables */
    extern integer cardc_(char *, ftnlen);
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    extern integer bsrchc_(char *, integer *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int chkout_(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Determine whether an item is an element of a character set. */

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

/*     SETS */

/* $ Keywords */

/*     CELLS */
/*     SETS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     ITEM       I   Item to be tested. */
/*     A          I   Set to be tested. */

/*     The function returns .TRUE. if ITEM is an element of set A. */

/* $ Detailed_Input */

/*     ITEM     is an item which may or may not be an element of the */
/*              input set. Trailing blanks in ITEM are not significant. */

/*     A        is a SPICE set. Trailing blanks in the members of A */
/*              are not significant. */

/* $ Detailed_Output */

/*     The function returns .TRUE. if ITEM is a member of the set A, */
/*     and returns .FALSE. otherwise. */

/*     The comparison between ITEM and members of A is case-sensitive. */
/*     Trailing blanks are ignored. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     None. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     The LOGICAL functions ELEMC, ELEMD and ELEMI correspond to the */
/*     set operator IN in the Pascal language. */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */

/*     1) Check if the elements of a list of body names belong to the */
/*        Solar System planets set. */


/*        Example code begins here. */


/*              PROGRAM ELEMC_EX1 */
/*              IMPLICIT NONE */

/*        C */
/*        C     SPICELIB functions. */
/*        C */
/*              LOGICAL                 ELEMC */

/*        C */
/*        C     Local constants. */
/*        C */
/*              INTEGER                 LBCELL */
/*              PARAMETER             ( LBCELL = -5 ) */

/*              INTEGER                 LISTSZ */
/*              PARAMETER             ( LISTSZ   = 6   ) */

/*              INTEGER                 PNAMSZ */
/*              PARAMETER             ( PNAMSZ   = 7 ) */

/*              INTEGER                 SETDIM */
/*              PARAMETER             ( SETDIM   = 9   ) */

/*        C */
/*        C     Local variables. */
/*        C */
/*              CHARACTER*(PNAMSZ)      ITEMS  ( LISTSZ        ) */
/*              CHARACTER*(PNAMSZ)      PLNETS ( LBCELL:SETDIM ) */

/*              INTEGER                 I */

/*        C */
/*        C     Create the original planets set and a list of body */
/*        C     names. */
/*        C */
/*              DATA                  ( PLNETS(I), I=1,SETDIM)  / */
/*             .                       'MERCURY', 'VENUS',   'EARTH', */
/*             .                       'MARS',    'JUPITER', 'SATURN', */
/*             .                       'URANUS',  'NEPTUNE', 'PLUTO'  / */

/*              DATA                    ITEMS / */
/*             .                            'EARTH', 'APOLLO', 'MARS', */
/*             .                            'PLUTO', 'VENUS', 'CERES' / */

/*        C */
/*        C     Validate the set: Initialize the non-empty set, remove */
/*        C     duplicates and sort the elements. */
/*        C */
/*              CALL VALIDC ( SETDIM, SETDIM, PLNETS ) */

/*        C */
/*        C     Check if the items in the list belong to the set. */
/*        C */
/*              DO I = 1, LISTSZ */

/*                 IF ( ELEMC ( ITEMS(I), PLNETS ) ) THEN */

/*                    WRITE(*,*) 'Item ', ITEMS(I), ' is in the set.' */

/*                 ELSE */

/*                    WRITE(*,*) 'Item ', ITEMS(I), */
/*             .                 ' is NOT in the set.' */

/*                 END IF */

/*              END DO */

/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, the output was: */


/*         Item EARTH   is in the set. */
/*         Item APOLLO  is NOT in the set. */
/*         Item MARS    is in the set. */
/*         Item PLUTO   is in the set. */
/*         Item VENUS   is in the set. */
/*         Item CERES   is NOT in the set. */


/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     C.A. Curzon        (JPL) */
/*     J. Diaz del Rio    (ODC Space) */
/*     H.A. Neilan        (JPL) */
/*     W.L. Taber         (JPL) */
/*     I.M. Underwood     (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.2.0, 24-AUG-2021 (JDR) */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. Added complete */
/*        code example. */

/*        Updated description of arguments ITEM and A to indicate that */
/*        trailing blanks are not significant and extended */
/*        $Detailed_Output to indicate that comparison is case-sensitive. */

/*        Removed unnecessary $Revisions section. */

/* -    SPICELIB Version 1.1.0, 17-MAY-1994 (HAN) */

/*        If the value of the function RETURN is .TRUE. upon execution of */
/*        this module, this function is assigned a default value of */
/*        either 0, 0.0D0, .FALSE., or blank depending on the type of */
/*        the function. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (CAC) (WLT) (IMU) (NJB) */

/* -& */
/* $ Index_Entries */

/*     element of a character set */

/* -& */

/*     SPICELIB functions */


/*     Standard error handling: */

    if (return_()) {
	ret_val = FALSE_;
	return ret_val;
    } else {
	chkin_("ELEMC", (ftnlen)5);
    }

/*     Just a binary search. */

    i__1 = cardc_(a, a_len);
    ret_val = bsrchc_(item, &i__1, a + a_len * 6, item_len, a_len) != 0;
    chkout_("ELEMC", (ftnlen)5);
    return ret_val;
} /* elemc_ */

