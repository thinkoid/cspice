/*

-Procedure removi_c ( Remove an item from an integer set )

-Abstract

   Remove an item from an integer set.

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

   void removi_c ( SpiceInt        item,
                   SpiceCell     * a    )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   item       I   Item to be removed.
   a         I-O  Removal set.

-Detailed_Input

   item        is an item which is to be removed from the specified set.
               `item' may or may not already be an element of the set.

   a           is a SPICE set.

               On input, `a' may or may not contain the input item as an
               element.

               `a' must be declared as an integer SpiceCell.

               CSPICE provides the following macro, which declares and
               initializes the cell

                  SPICEINT_CELL           ( a, ASZ );

               where ASZ is the maximum capacity of `a'.

-Detailed_Output

   a           on output, contains the difference of the input set and
               the input item. If the item is not an element of the set,
               the set is not changed.

-Parameters

   None.

-Exceptions

   1)  The data values in set `a' must be monotone strictly increasing.
       This is not checked. If this condition is not met, the results
       are unpredictable.

   2)  If the `a' cell argument has a type other than SpiceInt, the
       error SPICE(TYPEMISMATCH) is signaled.

   3)  If the `a' cell argument does not qualify as a SPICE set, the
       error SPICE(NOTASET) is signaled. SPICE sets have their data
       elements stored in increasing order and contain no duplicate
       elements.

-Files

   None.

-Particulars

   None.

-Examples

   The numerical results shown for this example may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

   1) Create an integer set for ten elements, insert items
      to it and then remove the even values.


      Example code begins here.


      /.
         Program removi_ex1
      ./
      #include <stdio.h>
      #include <cspice/SpiceUsr.h>

      int main( )
      {

         /.
         Local constants.
         ./
         #define SETDIM       10

         /.
         Local variables.
         ./
         SPICEINT_CELL      ( a     , SETDIM );
         SpiceInt             i;

         /.
         Create a list of items and even numbers.
         ./
         SpiceInt             even   [SETDIM] = {  0,  2,  4,  6,  8,
                                                  10, 12, 14, 16, 18  };

         SpiceInt             items  [SETDIM] = {  0,  1,  1,  2,  3,
                                                   5,  8, 10, 13, 21  };

         /.
         Initialize the empty set.
         ./
         valid_c ( SETDIM, 0, &a );

         /.
         Insert the list of integers into the set. If the item is
         an element of the set, the set is not changed.
         ./
         for ( i = 0; i < SETDIM; i++ )
         {
            insrti_c ( items[i], &a );
         }

         /.
         Output the original contents of set `a'.
         ./
         printf( "Items in original set A:\n" );

         for ( i = 0; i < card_c( &a ); i++ )
         {
            printf( "%6d", SPICE_CELL_ELEM_I( &a, i ) );
         }

         printf( " \n" );

         /.
         Remove the even values. If the item is not an element of
         the set, the set is not changed.
         ./
         for ( i = 0; i < SETDIM; i++ )
         {
            removi_c ( even[i], &a );
         }

         /.
         Output the contents of `a'.
         ./
         printf( "Odd numbers in set A:\n" );

         for ( i = 0; i < card_c( &a ); i++ )
         {
            printf( "%6d", SPICE_CELL_ELEM_I( &a, i ) );
         }

         printf( " \n" );

         return ( 0 );
      }


      When this program was executed on a Mac/Intel/cc/64-bit
      platform, the output was:


      Items in original set A:
           0     1     2     3     5     8    10    13    21
      Odd numbers in set A:
           1     3     5    13    21


-Restrictions

   None.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   C.A. Curzon         (JPL)
   J. Diaz del Rio     (ODC Space)
   W.L. Taber          (JPL)
   I.M. Underwood      (JPL)

-Version

   -CSPICE Version 1.1.0, 24-AUG-2021 (JDR)

       Changed the argument name "set" to "a" for consistency with other
       routines.

       Edited the header to comply with NAIF standard. Added complete code
       example.

       Extended description of argument "a" in -Detailed_Input to include
       type and preferred declaration method.

       Added entry #1 in -Exceptions section.

   -CSPICE Version 1.0.0, 07-AUG-2002 (NJB) (CAC) (WLT) (IMU)

-Index_Entries

   remove an item from an integer set

-&
*/

{
   /*
   local variables
   */
   SpiceBoolean            inSet;

   SpiceInt                i;
   SpiceInt              * idata;
   SpiceInt                loc;


   /*
   Use discovery check-in.
   */

   /*
   Make sure we're working with an integer cell.
   */
   CELLTYPECHK ( CHK_DISCOVER, "removi_c", SPICE_INT, a );

   idata = (SpiceInt *) (a->data);


   /*
   Make sure the cell is really a set.
   */
   CELLISSETCHK ( CHK_DISCOVER, "removi_c", a );


   /*
   Initialize the set if necessary.
   */
   CELLINIT ( a );


   /*
   Is the item in the set? If not, we're done now.
   */
   loc   =  lstlei_c ( item,  a->card,  idata );

   inSet =  (  loc  >  -1  ) && ( item == idata[loc] );

   if ( !inSet )
   {
      return;
   }


   /*
   Shift the set's contents to overwrite the slot at index loc.
   */
   for (  i = loc;   i < (a->card) - 1;   i++  )
   {
      idata[i] = idata[i+1];
   }


   /*
   Decrement the set's cardinality.
   */
   (a->card) --;


   /*
   Sync the set.
   */
   zzsynccl_c ( C2F, a );
}
