/* dlafps.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* $Procedure DLAFPS ( DLA, find previous segment ) */
/* Subroutine */ int dlafps_(integer *handle, integer *dladsc, integer *
	prvdsc, logical *found)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    extern /* Subroutine */ int chkin_(char *, ftnlen), dasrdi_(integer *, 
	    integer *, integer *, integer *), chkout_(char *, ftnlen);
    extern logical return_(void);
    integer bwd;

/* $ Abstract */

/*     Find the segment preceding a specified segment in a DLA file. */

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

/*     DAS */
/*     DLA */

/* $ Keywords */

/*     DAS */
/*     DLA */
/*     FILES */
/*     SEARCH */

/* $ Declarations */

/*     Include file dla.inc */

/*     This include file declares parameters for DLA format */
/*     version zero. */

/*        Version 3.0.1 17-OCT-2016 (NJB) */

/*           Corrected comment: VERIDX is now described as a DAS */
/*           integer address rather than a d.p. address. */

/*        Version 3.0.0 20-JUN-2006 (NJB) */

/*           Changed name of parameter DSCSIZ to DLADSZ. */

/*        Version 2.0.0 09-FEB-2005 (NJB) */

/*           Changed descriptor layout to make backward pointer */
/*           first element.  Updated DLA format version code to 1. */

/*           Added parameters for format version and number of bytes per */
/*           DAS comment record. */

/*        Version 1.0.0 28-JAN-2004 (NJB) */


/*     DAS integer address of DLA version code. */


/*     Linked list parameters */

/*     Logical arrays (aka "segments") in a DAS linked array (DLA) file */
/*     are organized as a doubly linked list.  Each logical array may */
/*     actually consist of character, double precision, and integer */
/*     components.  A component of a given data type occupies a */
/*     contiguous range of DAS addresses of that type.  Any or all */
/*     array components may be empty. */

/*     The segment descriptors in a SPICE DLA (DAS linked array) file */
/*     are connected by a doubly linked list.  Each node of the list is */
/*     represented by a pair of integers acting as forward and backward */
/*     pointers.  Each pointer pair occupies the first two integers of a */
/*     segment descriptor in DAS integer address space.  The DLA file */
/*     contains pointers to the first integers of both the first and */
/*     last segment descriptors. */

/*     At the DLA level of a file format implementation, there is */
/*     no knowledge of the data contents.  Hence segment descriptors */
/*     provide information only about file layout (in contrast with */
/*     the DAF system).  Metadata giving specifics of segment contents */
/*     are stored within the segments themselves in DLA-based file */
/*     formats. */


/*     Parameter declarations follow. */

/*     DAS integer addresses of first and last segment linked list */
/*     pointer pairs.  The contents of these pointers */
/*     are the DAS addresses of the first integers belonging */
/*     to the first and last link pairs, respectively. */

/*     The acronyms "LLB" and "LLE" denote "linked list begin" */
/*     and "linked list end" respectively. */


/*     Null pointer parameter. */


/*     Segment descriptor parameters */

/*     Each segment descriptor occupies a contiguous */
/*     range of DAS integer addresses. */

/*        The segment descriptor layout is: */

/*           +---------------+ */
/*           | BACKWARD PTR  | Linked list backward pointer */
/*           +---------------+ */
/*           | FORWARD PTR   | Linked list forward pointer */
/*           +---------------+ */
/*           | BASE INT ADDR | Base DAS integer address */
/*           +---------------+ */
/*           | INT COMP SIZE | Size of integer segment component */
/*           +---------------+ */
/*           | BASE DP ADDR  | Base DAS d.p. address */
/*           +---------------+ */
/*           | DP COMP SIZE  | Size of d.p. segment component */
/*           +---------------+ */
/*           | BASE CHR ADDR | Base DAS character address */
/*           +---------------+ */
/*           | CHR COMP SIZE | Size of character segment component */
/*           +---------------+ */

/*     Parameters defining offsets for segment descriptor elements */
/*     follow. */


/*     Descriptor size: */


/*     Other DLA parameters: */


/*     DLA format version.  (This number is expected to occur very */
/*     rarely at integer address VERIDX in uninitialized DLA files.) */


/*     Characters per DAS comment record. */


/*     End of include file dla.inc */

/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     HANDLE     I   Handle of open DLA file. */
/*     DLADSC     I   Descriptor of a segment in DLA file. */
/*     PRVDSC     O   Descriptor of previous segment in DLA file. */
/*     FOUND      O   Flag indicating whether a segment was found. */

/* $ Detailed_Input */

/*     HANDLE   is the integer handle associated with the file to be */
/*              searched. This handle is used to identify the file in */
/*              subsequent calls to other DLA or DAS routines. */

/*     DLADSC   is the descriptor of a DLA segment in the file */
/*              associated with HANDLE. The descriptor of the */
/*              segment preceding DLADSC is sought. */

/*              The segment descriptor layout is: */

/*                 +---------------+ */
/*                 | BACKWARD PTR  | Linked list backward pointer */
/*                 +---------------+ */
/*                 | FORWARD PTR   | Linked list forward pointer */
/*                 +---------------+ */
/*                 | BASE INT ADDR | Base DAS integer address */
/*                 +---------------+ */
/*                 | INT COMP SIZE | Size of integer segment component */
/*                 +---------------+ */
/*                 | BASE DP ADDR  | Base DAS d.p. address */
/*                 +---------------+ */
/*                 | DP COMP SIZE  | Size of d.p. segment component */
/*                 +---------------+ */
/*                 | BASE CHR ADDR | Base DAS character address */
/*                 +---------------+ */
/*                 | CHR COMP SIZE | Size of character segment component */
/*                 +---------------+ */

/* $ Detailed_Output */

/*     PRVDSC   is the descriptor of the DLA segment preceding the */
/*              segment associated with the input argument DLADSC. */

/*              PRVDSC is valid only if the output argument FOUND is */
/*              .TRUE. */

/*     FOUND    is a logical flag indicating whether the previous */
/*              segment was found. FOUND has the value .TRUE. if the */
/*              segment was found; otherwise FOUND is .FALSE. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If the input file handle is invalid, an error is */
/*         signaled by a routine in the call tree of this routine. */

/*     2)  If a failure occurs while reading the DLA file, an error */
/*         is signaled by a routine in the call tree of this routine. */

/* $ Files */

/*     See description of input argument HANDLE. */

/* $ Particulars */

/*     DLA files are built using the DAS low-level format; DLA files are */
/*     a specialized type of DAS file in which data are organized as a */
/*     doubly linked list of segments. Each segment's data belong to */
/*     contiguous components of character, double precision, and integer */
/*     type. */

/*     This routine supports backward traversal of a DLA file's segment */
/*     list. A backward traversal may be started from any segment in */
/*     the file; it is not necessary to call DLABBS first. The role of */
/*     DLABBS is simply to return the descriptor of the last segment in */
/*     the file. */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */

/*     1) Open a DLA file for read access, traverse the segment */
/*        list from back to front, and display segment address */
/*        and size attributes. */


/*        Example code begins here. */


/*              PROGRAM DLAFPS_EX1 */
/*              IMPLICIT NONE */

/*              INCLUDE 'dla.inc' */

/*        C */
/*        C     Local parameters */
/*        C */
/*              INTEGER               FILSIZ */
/*              PARAMETER           ( FILSIZ = 255 ) */

/*        C */
/*        C     Local variables */
/*        C */
/*              CHARACTER*(FILSIZ)    FNAME */

/*              INTEGER               CURRNT ( DLADSZ ) */
/*              INTEGER               DLADSC ( DLADSZ ) */
/*              INTEGER               HANDLE */
/*              INTEGER               NSEGS */
/*              INTEGER               SEGNO */

/*              LOGICAL               FOUND */

/*        C */
/*        C     Prompt for the name of the file to search. */
/*        C */
/*              CALL PROMPT ( 'Name of DLA file > ', FNAME ) */

/*        C */
/*        C     Open the DLA file for read access.  Since DLA */
/*        C     files use the DAS architecture, we can use DAS */
/*        C     routines to open and close the file. */
/*        C */
/*              CALL DASOPR ( FNAME, HANDLE ) */

/*        C */
/*        C     Count the segments in the file; this allows us */
/*        C     to label the segments in our display. */
/*        C */
/*              NSEGS = 0 */
/*              CALL DLABBS ( HANDLE, DLADSC, FOUND ) */

/*              DO WHILE ( FOUND ) */

/*                 NSEGS = NSEGS + 1 */
/*                 CALL MOVEI  ( DLADSC, DLADSZ, CURRNT        ) */
/*                 CALL DLAFPS ( HANDLE, CURRNT, DLADSC, FOUND ) */

/*              END DO */

/*        C */
/*        C     Begin a backward search.  Let DLADSC contain */
/*        C     the descriptor of the last segment. */
/*        C */
/*              SEGNO = NSEGS + 1 */

/*              CALL DLABBS ( HANDLE, DLADSC, FOUND ) */

/*              DO WHILE ( FOUND ) */
/*        C */
/*        C        Display the contents of the current segment */
/*        C        descriptor. */
/*        C */
/*                 SEGNO = SEGNO - 1 */

/*                 WRITE (*,*) ' ' */
/*                 WRITE (*,*) ' ' */
/*                 WRITE (*,*) 'Segment number = ', SEGNO */
/*                 WRITE (*,*) ' ' */
/*                 WRITE (*,*) 'Backward segment pointer         = ', */
/*             .               DLADSC(BWDIDX) */
/*                 WRITE (*,*) 'Forward segment pointer          = ', */
/*             .               DLADSC(FWDIDX) */
/*                 WRITE (*,*) 'Character component base address = ', */
/*             .               DLADSC(CBSIDX) */
/*                 WRITE (*,*) 'Character component size         = ', */
/*             .               DLADSC(CSZIDX) */
/*                 WRITE (*,*) 'D.p. base address                = ', */
/*             .               DLADSC(DBSIDX) */
/*                 WRITE (*,*) 'D.p. component size              = ', */
/*             .               DLADSC(DSZIDX) */
/*                 WRITE (*,*) 'Integer base address             = ', */
/*             .               DLADSC(IBSIDX) */
/*                 WRITE (*,*) 'Integer component size           = ', */
/*             .               DLADSC(ISZIDX) */
/*                 WRITE (*,*) ' ' */

/*        C */
/*        C        Find the previous segment. */
/*        C */
/*        C        To avoid using DLADSC as both input and output */
/*        C        in the following call (this use is not allowed */
/*        C        by the ANSI Fortran 77 standard), we copy DLADSC */
/*        C        into the variable CURRNT.  We then find the */
/*        C        segment preceding CURRNT. */
/*        C */
/*                 CALL MOVEI  ( DLADSC, DLADSZ, CURRNT        ) */
/*                 CALL DLAFPS ( HANDLE, CURRNT, DLADSC, FOUND ) */

/*              END DO */

/*        C */
/*        C     Close the file using the DAS close routine. */
/*        C */
/*              CALL DASCLS ( HANDLE ) */

/*              END */


/*        When this program was executed on a Mac/Intel/gfortran/64-bit */
/*        platform, using the DSK file named phobos512.bds, the output */
/*        was: */


/*        Name of DLA file > phobos512.bds */


/*         Segment number =            1 */

/*         Backward segment pointer         =           -1 */
/*         Forward segment pointer          =           -1 */
/*         Character component base address =            0 */
/*         Character component size         =            0 */
/*         D.p. base address                =            0 */
/*         D.p. component size              =      4737076 */
/*         Integer base address             =           11 */
/*         Integer component size           =     29692614 */


/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     J. Diaz del Rio    (ODC Space) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 06-JUL-2021 (JDR) */

/*        Changed input argument name DESCR to DLADSC for consistency */
/*        with other routines. */

/*        Edited the header to comply with NAIF standard. */
/*        Added solution for code example. */

/* -    SPICELIB Version 1.0.0, 06-JAN-2017 (NJB) */

/*     Original version 21-APR-2010 (NJB) */

/* -& */
/* $ Index_Entries */

/*     find previous segment in DLA file */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    }
    chkin_("DLAFPS", (ftnlen)6);

/*     Nothing found yet. */

    *found = FALSE_;

/*     Extract the backward pointer from the segment descriptor. */

    bwd = dladsc[0];
    if (bwd == -1) {

/*        There is no segment preceding the input segment. */

	chkout_("DLAFPS", (ftnlen)6);
	return 0;
    }

/*     Look up the previous descriptor */

    i__1 = bwd + 7;
    dasrdi_(handle, &bwd, &i__1, prvdsc);
    *found = TRUE_;
    chkout_("DLAFPS", (ftnlen)6);
    return 0;
} /* dlafps_ */

