/* elemi.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure ELEMI ( Element of an integer set ) */
logical elemi_(integer *item, integer *a)
{
    /* System generated locals */
    integer i__1;
    logical ret_val;

    /* Local variables */
    extern integer cardi_(integer *);
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    extern integer bsrchi_(integer *, integer *, integer *);
    extern /* Subroutine */ int chkout_(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Determine whether an item is an element of an integer set. */

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

/*     ITEM     is an item which may or may not be an element of */
/*              the input set. */

/*     A        is a SPICE set. */

/* $ Detailed_Output */

/*     The function returns .TRUE. if ITEM is a member of the set A, */
/*     and returns .FALSE. otherwise. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     None. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     The LOGICAL functions ELEMC, ELEMD and ELEMI correspond to the */
/*     set operator IN in the Pascal language. */

/*     This routine uses a binary search to check for the presence in */
/*     the set of the specified ITEM. */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */

/*     1) Check if the elements of a list of integers belong to a given */
/*        integer set. */


/*        Example code begins here. */


/*              PROGRAM ELEMI_EX1 */
/*              IMPLICIT NONE */

/*        C */
/*        C     SPICELIB functions. */
/*        C */
/*              LOGICAL                 ELEMI */

/*        C */
/*        C     Local constants. */
/*        C */
/*              INTEGER                 LBCELL */
/*              PARAMETER             ( LBCELL = -5 ) */

/*              INTEGER                 LISTSZ */
/*              PARAMETER             ( LISTSZ   = 6   ) */

/*              INTEGER                 SETDIM */
/*              PARAMETER             ( SETDIM   = 8   ) */

/*        C */
/*        C     Local variables. */
/*        C */
/*              INTEGER                 A      ( LBCELL:SETDIM ) */

/*              INTEGER                 I */
/*              INTEGER                 ITEMS  ( LISTSZ        ) */

/*        C */
/*        C     Set the values of the set and the list of integers. */
/*        C */
/*              DATA                  ( A(I), I=1,SETDIM)  / */
/*             .                           -1, 0, 1, 1, 3, 5, 0, -3 / */

/*              DATA                    ITEMS /  6, -1, 0, 2, 3, -2 / */

/*        C */
/*        C     Validate the set: Initialize the non-empty set, remove */
/*        C     duplicates and sort the elements. */
/*        C */
/*              CALL VALIDI ( SETDIM, SETDIM, A ) */

/*        C */
/*        C     Check if the items in the list belong to the set. */
/*        C */
/*              DO I = 1, LISTSZ */

/*                 IF ( ELEMI ( ITEMS(I), A ) ) THEN */

/*                    WRITE(*,'(A,I4,A)') 'Item ', ITEMS(I), */
/*             .                          ' is in the set.' */

/*                 ELSE */

/*                    WRITE(*,'(A,I4,A)') 'Item ', ITEMS(I), */
/*             .                          ' is NOT in the set.' */

/*                 END IF */

/*              END DO */

/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, the output was: */


/*        Item    6 is NOT in the set. */
/*        Item   -1 is in the set. */
/*        Item    0 is in the set. */
/*        Item    2 is NOT in the set. */
/*        Item    3 is in the set. */
/*        Item   -2 is NOT in the set. */


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

/*     element of an integer set */

/* -& */

/*     SPICELIB functions */


/*     Standard error handling: */

    if (return_()) {
	ret_val = FALSE_;
	return ret_val;
    } else {
	chkin_("ELEMI", (ftnlen)5);
    }

/*     Just a binary search. */

    i__1 = cardi_(a);
    ret_val = bsrchi_(item, &i__1, &a[6]) != 0;
    chkout_("ELEMI", (ftnlen)5);
    return ret_val;
} /* elemi_ */

