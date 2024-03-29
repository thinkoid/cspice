/*

-Procedure elemd_c ( Element of a double precision set )

-Abstract

   Determine whether an item is an element of a double precision set.

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

   SETS

-Keywords

   CELLS
   SETS

*/

   #include <cspice/SpiceUsr.h>
   #include <cspice/SpiceZfc.h>
   #include <cspice/SpiceZmc.h>

   SpiceBoolean elemd_c ( SpiceDouble     item,
                          SpiceCell     * a    )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   item       I   Item to be tested.
   a          I   Set to be tested.

   The function returns SPICETRUE if `item' is an element of `a'.

-Detailed_Input

   item        is an item which may or may not be an element of the
               input set.

   a           is a SPICE set.

               `a' must be declared as a double precision SpiceCell.

               CSPICE provides the following macro, which declares and
               initializes the cell

                  SPICEDOUBLE_CELL        ( a, ASZ );

               where ASZ is the maximum capacity of `a'.

-Detailed_Output

   The function returns SPICETRUE if `item' is a member of the set `a', and
   returns SPICEFALSE otherwise.

-Parameters

   None.

-Exceptions

   1)  If the `a' cell argument has a type other than SpiceDouble,
       the error SPICE(TYPEMISMATCH) is signaled. The function
       returns the value SPICEFALSE.

   2)  If the `a' cell argument does not qualify as a SPICE set, the
       error SPICE(NOTASET) is signaled. SPICE sets have their data
       elements stored in increasing order and contain no duplicate
       elements. The function returns the value SPICEFALSE.

-Files

   None.

-Particulars

   This routine uses a binary search to check for the presence in the set
   of the specified item.

-Examples

   The numerical results shown for this example may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) Check if the elements of a list of double precision numbers
      belong to a given double precision set.

      Example code begins here.


      /.
         Program elemd_ex1
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {

         /.
         Local constants.
         ./
         #define LISTSZ       6
         #define SETDIM       8

         /.
         Local variables.
         ./
         SPICEDOUBLE_CELL   ( a     , SETDIM );
         SpiceInt             i;

         /.
         Set the values of the set and the list of double
         precision numbers.
         ./
         SpiceDouble          values [SETDIM] = {
                                             -1.0, 0.0, 1.0,  1.0,
                                              3.0, 5.0, 0.0, -3.0 };

         SpiceDouble          items  [LISTSZ] = { 6.0, -1.0,  0.0,
                                                  2.0,  3.0, -2.0 };

         /.
         Add the values to the integer set using appndd_c. The
         results of these calls results in a cell which does not
         qualify as a set.
         ./
         for ( i = 0; i < SETDIM; i++ )
         {
            appndd_c ( values[i], &a );
         }

         /.
         Initialize the set by validating the cell: remove duplicates
         and sort the elements in increasing order.
         ./
         valid_c ( SETDIM, SETDIM, &a );

         /.
         Check if the items in the list belong to the set.
         ./
         for ( i = 0; i < LISTSZ; i++ )
         {
            if ( elemd_c ( items[i], &a ) )
            {
               printf( "Item %5.1f is in the set.\n", items[i] );
            }
            else
            {
               printf( "Item %5.1f is NOT in the set.\n", items[i] );
            }
         }

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Item   6.0 is NOT in the set.
      Item  -1.0 is in the set.
      Item   0.0 is in the set.
      Item   2.0 is NOT in the set.
      Item   3.0 is in the set.
      Item  -2.0 is NOT in the set.


-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   C.A. Curzon         (JPL)
   J. Diaz del Rio     (ODC Space)
   H.A. Neilan         (JPL)
   W.L. Taber          (JPL)
   I.M. Underwood      (JPL)

-Version

   -CSPICE Version 1.1.0, 24-AUG-2021 (JDR)

       Edited the -Examples section to comply with NAIF standard.
       Added complete code example.

       Changed the argument name "set" to "a" for consistency with other
       routines.

       Cast returned value type to SpiceBoolean.

       Extended description of argument "a" in -Detailed_Input to include
       type and preferred declaration method.

   -CSPICE Version 1.0.0, 07-AUG-2002 (NJB) (CAC) (HAN) (WLT) (IMU)

-Index_Entries

   element of a d.p. set

-&
*/

{

   /*
   Use discovery check-in.

   Make sure we're working with a double precision cell.
   */
   CELLTYPECHK_VAL ( CHK_DISCOVER, "elemd_c", SPICE_DP, a, SPICEFALSE );

   /*
   Make sure the input cell is a set.
   */
   CELLISSETCHK_VAL ( CHK_DISCOVER, "elemd_c", a, SPICEFALSE );

   /*
   Initialize the set if necessary.
   */
   CELLINIT ( a );

   /*
   The routine bsrchd_c returns the index of the item in the set,
   or -1 if the item is not present.
   */
   return (  ( SpiceBoolean )
             ( bsrchd_c ( item,  a->card,  a->data )  !=  -1 )  );
}
