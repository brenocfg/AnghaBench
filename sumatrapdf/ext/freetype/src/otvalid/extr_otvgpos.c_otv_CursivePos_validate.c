#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OTV_Validator ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int EntryAnchor ; 
 int ExitAnchor ; 
 int /*<<< orphan*/  FT_INVALID_FORMAT ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int /*<<< orphan*/  otv_Anchor_validate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otv_Coverage_validate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_CursivePos_validate( FT_Bytes       table,
                           OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   PosFormat;


    OTV_NAME_ENTER( "CursivePos" );

    OTV_LIMIT_CHECK( 2 );
    PosFormat = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (format %d)\n", PosFormat ));

    switch ( PosFormat )
    {
    case 1:     /* CursivePosFormat1 */
      {
        FT_UInt   table_size;
        FT_UInt   Coverage, EntryExitCount;

        OTV_OPTIONAL_TABLE( EntryAnchor );
        OTV_OPTIONAL_TABLE( ExitAnchor  );


        OTV_LIMIT_CHECK( 4 );
        Coverage       = FT_NEXT_USHORT( p );
        EntryExitCount = FT_NEXT_USHORT( p );

        OTV_TRACE(( " (EntryExitCount = %d)\n", EntryExitCount ));

        otv_Coverage_validate( table + Coverage,
                               otvalid,
                               (FT_Int)EntryExitCount );

        OTV_LIMIT_CHECK( EntryExitCount * 4 );

        table_size = EntryExitCount * 4 + 4;

        /* EntryExitRecord */
        for ( ; EntryExitCount > 0; EntryExitCount-- )
        {
          OTV_OPTIONAL_OFFSET( EntryAnchor );
          OTV_OPTIONAL_OFFSET( ExitAnchor  );

          OTV_SIZE_CHECK( EntryAnchor );
          if ( EntryAnchor )
            otv_Anchor_validate( table + EntryAnchor, otvalid );

          OTV_SIZE_CHECK( ExitAnchor );
          if ( ExitAnchor )
            otv_Anchor_validate( table + ExitAnchor, otvalid );
        }
      }
      break;

    default:
      FT_INVALID_FORMAT;
    }

    OTV_EXIT;
  }