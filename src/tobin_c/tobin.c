/* tobin.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <cspice/f2c.h>

/* Table of constant values */

static integer c__2 = 2;
static integer c__8 = 8;
static logical c_true = TRUE_;
static integer c__0 = 0;
static integer c__1 = 1;

/* $Procedure   TOBIN (Create a binary kernel for use on this machine) */
/* Main program */ MAIN__(void)
{
    /* Initialized data */

    static char binext[3*8] = "BSP" "BC " "BEE" "BPC" "BSP" "BC " "BEE" "BPC";
    static char xfrext[3*8] = "TSP" "TC " "TEE" "TPC" "XSP" "XC " "XEE" "XPC";

    /* System generated locals */
    address a__1[2];
    integer i__1[2], i__2, i__3;

    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen);
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen),
	     s_copy(char *, char *, ftnlen, ftnlen);
    integer s_rnge(char *, integer, char *, integer);

    /* Local variables */
    static char arch[3], line[512], type__[4];
    extern /* Subroutine */ int zzgetfat_(char *, char *, char *, integer *, 
	    ftnlen, ftnlen, ftnlen), zzconvtb_(char *, char *, char *, char *,
	     integer *, ftnlen, ftnlen, ftnlen, ftnlen);
    static integer i__;
    extern integer cardi_(integer *);
    extern /* Subroutine */ int lcase_(char *, char *, ftnlen, ftnlen), 
	    chkin_(char *, ftnlen), ucase_(char *, char *, ftnlen, ftnlen), 
	    errch_(char *, char *, ftnlen, ftnlen), repmc_(char *, char *, 
	    char *, char *, ftnlen, ftnlen, ftnlen, ftnlen), reset_(void);
    extern integer cposr_(char *, char *, integer *, ftnlen, ftnlen), rtrim_(
	    char *, ftnlen);
    extern /* Subroutine */ int ljust_(char *, char *, ftnlen, ftnlen);
    static integer basbeg;
    extern logical failed_(void);
    extern /* Subroutine */ int dafhof_(integer *), dafcls_(integer *), 
	    cleari_(integer *, integer *), delfil_(char *, ftnlen), scardi_(
	    integer *, integer *), dashof_(integer *);
    static char binfnm[128];
    extern /* Subroutine */ int dascls_(integer *);
    extern integer isrchc_(char *, integer *, char *, ftnlen, ftnlen);
    static char bslash[1];
    extern /* Subroutine */ int getcml_(char *, ftnlen), erract_(char *, char 
	    *, ftnlen, ftnlen), byebye_(char *, ftnlen);
    static char kerlin[132], pthchr[3];
    static integer number;
    extern /* Subroutine */ int sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen);
    static char termin[5], xfrfnm[128];
    extern /* Subroutine */ int setmsg_(char *, ftnlen);
    static integer idxext, dotpos, opnset[7], numopn;
    extern /* Subroutine */ int nextwd_(char *, char *, char *, ftnlen, 
	    ftnlen, ftnlen), errprt_(char *, char *, ftnlen, ftnlen);
    extern logical exists_(char *, ftnlen);
    static char extnsn[3];
    extern /* Subroutine */ int tostdo_(char *, ftnlen), zzascii_(char *, 
	    char *, logical *, char *, ftnlen, ftnlen, ftnlen);

/* $ Abstract */

/*     TOBIN is a utility program that converts a SPICE transfer format */
/*     file into it's binary format for use in a particular computing */
/*     environment. */

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

/* $ Input */

/*     TOBIN requires at least the input transfer file name on the */
/*     command line. Optionally, a name for the output binary file may */
/*     be specified. If a name for the output file is provided on the */
/*     command line it overrides the automatic naming conventions used */
/*     by the program. */

/*     If only the name of the input transfer file is provided on the */
/*     command line, TOBIN will generate a name for the output binary */
/*     kernel file with the same base name as the input transfer file */
/*     and an appropriate filename extension, based on the filename */
/*     extension of the transfer file. If TOBIN does not recognize the */
/*     filename extension of the input transfer file, or there is no */
/*     filename extension on the input transfer file, a filename */
/*     extension of '.bin' will be used as the filename extension of the */
/*     output binary file. */

/*     If a filename for the output binary kernel is provided on the */
/*     command line it will be used as the name of the output file */
/*     regardless of the name of the input transfer file. */

/*     TOBIN recognizes the filename extensions in the left hand column */
/*     below and converts them into the corresponding filename */
/*     extensions in the right hand column. */

/*        'tc'   --> 'bc' */
/*        'tee'  --> 'bee' */
/*        'tpc'  --> 'bpc' */
/*        'tsp'  --> 'bsp' */
/*        'xc'   --> 'bc' */
/*        'xee'  --> 'bee' */
/*        'xpc'  --> 'bpc' */
/*        'xsp'  --> 'bsp' */

/* $ Output */

/*     TOBIN creates a binary format kernel file from the input transfer */
/*     file specified on the command line. */

/* $ Particulars */

/*     The usage of TOBIN is shown below: */

/*     tobin input_file [output_file] */

/*     The first word following the command must be the input filename */
/*     and the second if it appears, must be the output file name. */

/*     If the output file already exists, TOBIN signals an error and */
/*     stops. We assume that it is bad form to stomp on a file without */
/*     telling you about it. */

/*     The text transfer file may include text data preceding the line */
/*     identifying the file as a SPICE transfer file.  An example of such */
/*     an ID info line: */

/*        DAFETF NAIF DAF ENCODED TRANSFER FILE */

/*     A transfer file with some sort of non-SPICE text header has the */
/*     structure: */

/*        ___________ */
/*       | */
/*       | */
/*       | */
/*       |   ...some text... */
/*       | */
/*       | */
/*       | */
/*       |___________ */
/*       DAFETF NAIF DAF ENCODED TRANSFER FILE */
/*             ...unmodified transfer file text.... */

/*     The text preceding the info line is ignored:  WARNING, if */
/*     the text header contains a valid SPICE ID string (DAFETF */
/*     for example), the program assumes all data after that line */
/*     is the transfer file data.  Something will break. */

/* $ Examples */

/*     Example 1: */

/*        Convert the transfer file 'ephem.xsp' into a binary kernel */
/*        file. */

/*           > tobin ephem.xsp */

/*        This will create the binary kernel file 'ephem.bsp'. */

/*     Example 2: */

/*        This is the same as Example 1, except we explicitly set the */
/*        output filename on the command line. */

/*           > tobin ephem.xsp myephem.bsp */

/*        This will create the binary kernel file 'myephem.bsp'. */

/*     Example 3: */

/*        For this example, we provide a filename extension on the input */
/*        transfer file that TOBIN does not recognize. */

/*           > tobin mydata.ttt */

/*        This will create the binary file 'mydata.bin'. */

/* $ References */

/*     For additional information, see the TOBIN User's Guide. */

/* $ Version */

/* -    SPICELIB Version 1.4.0  28-APR-2014 (BVS) */

/*        Updated to return with success or failure status. */

/* -    SPICELIB Version 1.3.0  17-FEB-2004 (EDW) (BVS) */

/*        Added line terminator test via ZZASCII call that will signal */
/*        an error if the input text file is not native to the current */
/*        platform. */

/* -    SPICELIB Version 1.2.0  20-MAR-1999 (EDW) */

/*        Operation of the binary to transfer function enhanced to */
/*        accomodate SFDUs.  See the routines: ZZGETFAT 1.0.0; */
/*        ZZCONVTB 1.0.0 for details. */

/* -    SPICELIB Version 1.1.0, 07-DEC-1995 (KRG) */

/*        Changed the search direction for the dot '.' in a file name. */
/*        The search is now performed from right to left, so problems */
/*        with using ".." to refer to the parent directory in UNIX and */
/*        DOS are fixed. */

/*        Also, now only the base name of the file is searched for the */
/*        extension. */

/* -    SPICELIB Version 1.0.0, 11-AUG-1995 (KRG) */

/* -& */

/*     Spicelib functions */


/*     Parameters */

/*     Lower bound for a SPICELIB CELL data structure. */


/*     Maximum number of open binary files allowed. */


/*     Maximum number fo file extensions (types). */


/*     Line length. */


/*     Filename length. */


/*     Filename extension length. */


/*     Decimal code for the backslash character, '\'. */


/*     Set the length for the type of a file. */


/*     Set the length for the architecture of a file. */


/*     Set sizes of EOL type string and buffer string used to */
/*     call ZZASCII. */


/*     Local variables */


/*     Save everthing to keep configuration control happy. */


/*     Initial values. */


/*     Check into the error handling. */

    chkin_("TOBIN", (ftnlen)5);

/*     Set the error action to ABORT mode. For the first part of the */
/*     program we want to halt execution if an error occurs. Before the */
/*     conversion, we set the error action to RETURN mode so that we can */
/*     clean up if the conversion failed. */

    erract_("SET", "ABORT", (ftnlen)3, (ftnlen)5);

/*     Set the error messages that are printed. */

    errprt_("SET", "NONE, SHORT, LONG, TRACEBACK", (ftnlen)3, (ftnlen)28);

/*     Set the value of the backslash character. */

    *(unsigned char *)bslash = '\\';

/*     Get the command line arguments. */

    getcml_(line, (ftnlen)512);

/*     The minimum information we need to convert a file is the name of */
/*     the transfer file that is to be converted. We figure out the */
/*     extension for the output file from the extension of the input */
/*     file. If an output file name is provided that is used instead. */

    if (s_cmp(line, " ", (ftnlen)512, (ftnlen)1) == 0) {
	setmsg_("Usage: tobin file.x* [file.b*]", (ftnlen)30);
	sigerr_("SPICE(USAGEERROR)", (ftnlen)17);
    }

/*     Get the transfer filename. If there is a second filename for the */
/*     binary output file it will automatically appear in BINFNM. */

    nextwd_(line, xfrfnm, binfnm, (ftnlen)512, (ftnlen)128, (ftnlen)128);

/*     If there was no binary filename, figure out the extension for the */
/*     output file from the extension for the input file. If the */
/*     extension is not recognized, or there is no extension, the */
/*     extension '.bin' will be used. We search only the base name in */
/*     reverse. The base name is that part of the file name after */
/*     the last directory separator, a '/', '\', or ']'. */

    if (s_cmp(binfnm, " ", (ftnlen)128, (ftnlen)1) == 0) {
/* Writing concatenation */
	i__1[0] = 2, a__1[0] = "/]";
	i__1[1] = 1, a__1[1] = bslash;
	s_cat(pthchr, a__1, i__1, &c__2, (ftnlen)3);
	i__2 = rtrim_(xfrfnm, (ftnlen)128);
	basbeg = cposr_(xfrfnm, pthchr, &i__2, (ftnlen)128, (ftnlen)3) + 1;
	i__2 = rtrim_(xfrfnm + (basbeg - 1), 128 - (basbeg - 1));
	dotpos = cposr_(xfrfnm + (basbeg - 1), ".", &i__2, 128 - (basbeg - 1),
		 (ftnlen)1);
	if (dotpos > 0) {
	    dotpos = dotpos + basbeg - 1;
	    i__2 = dotpos;
	    s_copy(extnsn, xfrfnm + i__2, (ftnlen)3, dotpos + 3 - i__2);
	    ucase_(extnsn, extnsn, (ftnlen)3, (ftnlen)3);
	    idxext = isrchc_(extnsn, &c__8, xfrext, (ftnlen)3, (ftnlen)3);
	    if (idxext > 0) {
		s_copy(extnsn, binext + ((i__2 = idxext - 1) < 8 && 0 <= i__2 
			? i__2 : s_rnge("binext", i__2, "tobin_", (ftnlen)353)
			) * 3, (ftnlen)3, (ftnlen)3);
		lcase_(extnsn, extnsn, (ftnlen)3, (ftnlen)3);
/* Writing concatenation */
		i__1[0] = dotpos, a__1[0] = xfrfnm;
		i__1[1] = 3, a__1[1] = extnsn;
		s_cat(binfnm, a__1, i__1, &c__2, (ftnlen)128);
	    } else {
/* Writing concatenation */
		i__1[0] = dotpos, a__1[0] = xfrfnm;
		i__1[1] = 3, a__1[1] = "bin";
		s_cat(binfnm, a__1, i__1, &c__2, (ftnlen)128);
	    }
	} else {
/* Writing concatenation */
	    i__1[0] = rtrim_(xfrfnm, (ftnlen)128), a__1[0] = xfrfnm;
	    i__1[1] = 4, a__1[1] = ".bin";
	    s_cat(binfnm, a__1, i__1, &c__2, (ftnlen)128);
	}
    } else {
	ljust_(binfnm, binfnm, (ftnlen)128, (ftnlen)128);
    }

/*     If the output name already exists, we do not overwrite it, so */
/*     signal an error. */

    if (exists_(binfnm, (ftnlen)128)) {
	setmsg_("The output file '#' already exists.", (ftnlen)35);
	errch_("#", binfnm, (ftnlen)1, (ftnlen)128);
	sigerr_("SPICE(FILEALREADYEXISTS)", (ftnlen)24);
    }
    repmc_("Converting: #", "#", xfrfnm, line, (ftnlen)13, (ftnlen)1, (ftnlen)
	    128, (ftnlen)512);
    tostdo_(line, (ftnlen)512);
    repmc_("        To: #", "#", binfnm, line, (ftnlen)13, (ftnlen)1, (ftnlen)
	    128, (ftnlen)512);
    tostdo_(line, (ftnlen)512);

/*     Set the error action to return mode so that we can clean up if */
/*     there is an error. */

    erract_("SET", "RETURN", (ftnlen)3, (ftnlen)6);

/*     Check for line terminator compatibility with this platform. */

    zzascii_(xfrfnm, kerlin, &c_true, termin, (ftnlen)128, (ftnlen)132, (
	    ftnlen)5);

/*     Convert the file. */

    zzgetfat_(xfrfnm, arch, type__, &number, (ftnlen)128, (ftnlen)3, (ftnlen)
	    4);
    zzconvtb_(xfrfnm, arch, type__, binfnm, &number, (ftnlen)128, (ftnlen)3, (
	    ftnlen)4, (ftnlen)128);
    if (failed_()) {

/*     If we failed, reset the error handling and delete the binary file */
/*     that we were creating if it exists. */

	reset_();
	scardi_(&c__0, opnset);
	cleari_(&c__1, &opnset[6]);

/*        Get the handles for any DAF files which may still be */
/*        open and close them. */

	dafhof_(opnset);
	numopn = cardi_(opnset);
	if (numopn > 0) {
	    i__2 = numopn;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		dafcls_(&opnset[(i__3 = i__ + 5) < 7 && 0 <= i__3 ? i__3 : 
			s_rnge("opnset", i__3, "tobin_", (ftnlen)423)]);
	    }
	}

/*        Clear out any binary file handles in the open set, */
/*        OPNSET. */

	scardi_(&c__0, opnset);
	cleari_(&c__1, &opnset[6]);

/*        Get the handles for any DAS files which may still be */
/*        open and close them. */

	dashof_(opnset);
	numopn = cardi_(opnset);
	if (numopn > 0) {
	    i__2 = numopn;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		dascls_(&opnset[(i__3 = i__ + 5) < 7 && 0 <= i__3 ? i__3 : 
			s_rnge("opnset", i__3, "tobin_", (ftnlen)442)]);
	    }
	}
	if (exists_(binfnm, (ftnlen)128)) {
	    delfil_(binfnm, (ftnlen)128);
	}

/*        Call RESET one more time just in case there was an */
/*        error closing of deleting the file. */

	reset_();

/*        Stop with failure status. */

	byebye_("FAILURE", (ftnlen)7);
    }
    chkout_("TOBIN", (ftnlen)5);

/*     Stop with success status. */

    byebye_("SUCCESS", (ftnlen)7);
    return 0;
} /* MAIN__ */

/* Main program alias */ int tobin_ () { MAIN__ (); return 0; }
