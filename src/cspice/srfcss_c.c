/*

-Procedure srfcss_c ( Surface ID and body string to surface string )

-Abstract

   Translate a surface ID code, together with a body string, to the
   corresponding surface name. If no such surface name exists,
   return a string representation of the surface ID code.

-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading

   DSK
   NAIF_IDS

-Keywords

   CONVERSION
   DSK
   ID
   NAME
   STRING
   SURFACE

*/

   #include <cspice/SpiceUsr.h>
   #include <cspice/SpiceZfc.h>
   #include <cspice/SpiceZst.h>
   #include <cspice/SpiceZmc.h>


   void srfcss_c ( SpiceInt          code,
                   ConstSpiceChar  * bodstr,
                   SpiceInt          srflen,
                   SpiceChar       * srfstr,
                   SpiceBoolean    * isname )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   code       I   Integer surface ID code to translate to a string.
   bodstr     I   Name or ID of body associated with surface.
   srflen     I   Maximum length of output `srfstr'.
   srfstr     O   String corresponding to surface ID code.
   isname     O   Flag indicating whether output is a surface name.
   SPICE_SRF_SFNMLN
              P   Maximum length of surface name.

-Detailed_Input

   code        is an integer ID code for a surface associated with a
               specified body.


   bodstr      is a string designating the body associated with the
               input surface ID code. `bodstr' may contain a body name
               or a string representation of the body's integer ID
               code. For example, `bodstr' may contain

                  "1000012"

               instead of

                  '67P/CHURYUMOV-GERASIMENKO (1969 R1)'

               Case and leading and trailing blanks in a name are not
               significant. Sequences of consecutive embedded blanks
               are considered equivalent to a single blank. That is,
               all of the following strings are equivalent names:

                  '67P/CHURYUMOV-GERASIMENKO (1969 R1)'
                  '67P/Churyumov-Gerasimenko (1969 R1)'
                  '67P/CHURYUMOV-GERASIMENKO (1969 R1)   '
                  '67P/CHURYUMOV-GERASIMENKO    (1969 R1)'
                  '   67P/CHURYUMOV-GERASIMENKO (1969 R1)'

               However, '67P/CHURYUMOV-GERASIMENKO(1969R1)'
               is not equivalent to the names above.


   srflen      is the maximum number of characters that can be
               accommodated in the output string `srfstr'. This count
               includes room for the terminating null character.
               Normally `srflen' should be set to the value of the
               parameter SPICE_SRF_SFNMLN.

-Detailed_Output

   srfstr      the name of the surface identified by `code', for the body
               designated by `bodstr', if for this body an association
               exists between the input surface ID and a surface name.

               If `code' has more than one translation, then the most
               recently defined surface name corresponding to `code' is
               returned. `srfstr' will have the exact format (case and
               embedded blanks) used in the definition of the
               name/code association.

               If the input surface ID code and body name do not map
               to a surface name, `srfstr' is set to the string
               representation of `code'.

               `srfstr' should be declared with length

                  SPICE_SRF_SFNMLN

               (see the -Parameters section below).


   isname      is a logical flag that is SPICETRUE if a surface name
               corresponding to the input ID codes was found and
               SPICEFALSE otherwise. When `isname' is SPICEFALSE, the
               output string `srfstr' contains a string representing the
               integer `code'.

-Parameters

   SPICE_SRF_SFNMLN

              is the maximum length of a surface name. This
              parameter is declared in the CSPICE header file

                 SpiceSrf.h

-Exceptions

   1)  If the input body string cannot be mapped to a body name, the
       output `srfstr' is set to a string representation of the
       surface ID code. The output `isname' is set to SPICEFALSE.

       This case is not treated as an error.

   2)  If the input surface code cannot be mapped to a surface name,
       the output `srfstr' is set to a string representation of the
       surface ID code. The input body string is ignored. The output
       `isname' is set to SPICEFALSE.

       This case is not treated as an error.

   3)  If the `bodstr' input string pointer is null, the error
       SPICE(NULLPOINTER) is signaled.

   4)  If the `bodstr' input string has zero length, the error
       SPICE(EMPTYSTRING) is signaled.

   5)  If the `srfstr' output string pointer is null, the error
       SPICE(NULLPOINTER) is signaled.

   6)  If the `srfstr' output string has length less than two
       characters, the error SPICE(STRINGTOOSHORT) is signaled, since
       the output string is too short to contain one character of
       output data plus a null terminator.

-Files

   Surface name-to-ID mappings may be defined at run time by loading
   text kernels containing kernel variable assignments of the form

      NAIF_SURFACE_NAME += ( <surface name 1>, ... )
      NAIF_SURFACE_CODE += ( <surface code 1>, ... )
      NAIF_SURFACE_BODY += ( <body code 1>,    ... )

   Above, the Ith elements of the lists on the assignments' right
   hand sides together define the Ith surface name/ID mapping.

   The same effect can be achieved using assignments formatted as
   follows:

      NAIF_SURFACE_NAME += <surface name 1>
      NAIF_SURFACE_CODE += <surface code 1>
      NAIF_SURFACE_BODY += <body code 1>

      NAIF_SURFACE_NAME += <surface name 2>
      NAIF_SURFACE_CODE += <surface code 2>
      NAIF_SURFACE_BODY += <body code 2>

         ...

   Note the use of the

      +=

   operator; this operator appends to rather than overwrites the
   kernel variable named on the left hand side of the assignment.

-Particulars

   Surfaces are always associated with bodies (which usually are
   ephemeris objects). For any given body, a mapping between surface
   names and surface ID codes can be established.

   Bodies serve to disambiguate surface names and ID codes: the set
   of surface names and surface ID codes for a given body can be
   thought of as belonging to a name space. A given surface ID code
   or surface name may be used for surfaces of multiple bodies,
   without conflict.

   Associations between surface names and ID codes are always made
   via kernel pool assignments; there are no built-in associations.

   srfcss_c is one of four related functions:

      srfs2c_c      Surface string and body string to surface ID code
      srfscc_c      Surface string and body ID code to surface ID code
      srfc2s_c      Surface ID code and body ID code to surface string
      srfcss_c      Surface ID code and body string to surface string

   srfs2c_c, srfc2s_c, srfscc_c, and srfcss_c perform translations between
   surface strings and their corresponding integer ID codes.

   Refer to naif_ids.req for details concerning adding new surface
   name/code associations at run time by loading text kernels.

-Examples

   The numerical results shown for this example may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) Supposed a text kernel has been loaded that contains
      the following assignments:

         NAIF_SURFACE_NAME += ( 'MGS MOLA  64 pixel/deg',
                                'MGS MOLA 128 pixel/deg',
                                'PHOBOS GASKELL Q512'     )
         NAIF_SURFACE_CODE += (   1,   2,    1 )
         NAIF_SURFACE_BODY += ( 499, 499,  401 )

      Translate each surface and body ID code pair to the
      associated surface name. Also perform a translation
      for a surface ID having no matching name.

      Use the meta-kernel shown below to define the required SPICE
      kernel variables.


         KPL/MK

         File: srfcss_ex1.tm

         This meta-kernel is intended to support operation of SPICE
         example programs. The file contents shown here should not be
         assumed to contain adequate or correct versions of data
         required by SPICE-based user applications.


         \begindata

         NAIF_SURFACE_NAME += ( 'MGS MOLA  64 pixel/deg',
                                'MGS MOLA 128 pixel/deg',
                                'PHOBOS GASKELL Q512'     )
         NAIF_SURFACE_CODE += (   1,   2,    1 )
         NAIF_SURFACE_BODY += ( 499, 499,  401 )

         \begintext

         End of meta-kernel


      Example code begins here.


      /.
         Program srfcss_ex1
      ./

      #include <stdio.h>
      #include <cspice/SpiceUsr.h>


      int main()
      {
         /.
         Local constants
         ./
         #define BDNMLN          37
         #define NCASE           5

         /.
         Local variables
         ./
         SpiceBoolean            isname;

         SpiceChar               srfnam [ SPICE_SRF_SFNMLN ];

         static SpiceChar        tf     [2][6] =

                                    { "false", "true" };

         SpiceChar             * meta;

         static SpiceChar        bodstr [NCASE][BDNMLN] =

                                   { "MARS", "PHOBOS", "499",
                                     "MARS", "ZZZ"            };


         static SpiceInt         surfid [NCASE] =

                                    {   1,   1,   2,   3,  1 };

         SpiceInt                i;


         meta = "srfcss_ex1.tm";

         furnsh_c ( meta );

         printf ( "\n" );

         for ( i = 0;  i < NCASE;  i++ )
         {
            srfcss_c ( surfid[i], bodstr[i], SPICE_SRF_SFNMLN,
                       srfnam,    &isname                      );

            printf ( "surface ID       = %d\n"
                     "body string      = %s\n"
                     "name found       = %s\n"
                     "surface string   = %s\n\n",
                     (int) surfid[i],
                     bodstr[i],
                     tf[isname],
                     srfnam                     );
         }

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      surface ID       = 1
      body string      = MARS
      name found       = true
      surface string   = MGS MOLA  64 pixel/deg

      surface ID       = 1
      body string      = PHOBOS
      name found       = true
      surface string   = PHOBOS GASKELL Q512

      surface ID       = 2
      body string      = 499
      name found       = true
      surface string   = MGS MOLA 128 pixel/deg

      surface ID       = 3
      body string      = MARS
      name found       = false
      surface string   = 3

      surface ID       = 1
      body string      = ZZZ
      name found       = false
      surface string   = 1


-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   J. Diaz del Rio     (ODC Space)
   B.V. Semenov        (JPL)
   E.D. Wright         (JPL)

-Version

   -CSPICE Version 1.0.1, 10-AUG-2021 (JDR)

       Edited the header to comply with NAIF standard.

   -CSPICE Version 1.0.0, 05-APR-2017 (NJB) (BVS) (EDW)

-Index_Entries

   surface ID code and body string to surface string

-&
*/

{ /* Begin srfcss_c */



   /*
   Local variables
   */
   logical                 namfnd;

   /*
   Participate in error tracing.
   */
   chkin_c ( "srfcss_c" );

   /*
   Check the input string to make sure the pointer is non-null and
   the string length is non-zero.
   */
   CHKFSTR ( CHK_STANDARD, "srfcss_c", bodstr );

   /*
   Check the output string to make sure the pointer is non-null and
   the string length is at least 2.
   */
   CHKOSTR ( CHK_STANDARD, "srfcss_c", srfstr, srflen );

   /*
   Hand off the work to the f2c'd routine.
   */
   srfcss_ ( (integer    *) &code,
             (char       *) bodstr,
             (char       *) srfstr,
             (logical    *) &namfnd,
             (ftnlen      ) strlen(bodstr),
             (ftnlen      ) srflen-1        );

   /*
   Assign output SpiceBoolean found flag.
   */
   *isname = namfnd;

   /*
   Convert `srfstr' to a null-terminated C string. This operation is
   valid whether or not the CSPICE routine signaled an error or failed
   to translate the input code.
   */
   F2C_ConvertStr ( srflen, srfstr );


   chkout_c ( "srfcss_c" );

} /* End srfcss_c */
