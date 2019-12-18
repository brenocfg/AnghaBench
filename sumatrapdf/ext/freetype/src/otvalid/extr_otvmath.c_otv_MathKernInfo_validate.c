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
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 scalar_t__ Coverage ; 
 int FT_NEXT_USHORT (scalar_t__) ; 
 scalar_t__ MKRecordOffset ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (scalar_t__) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (scalar_t__) ; 
 int /*<<< orphan*/  otv_Coverage_validate (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otv_MathKern_validate (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_MathKernInfo_validate( FT_Bytes       table,
                             OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   i, j, cnt, table_size;

    OTV_OPTIONAL_TABLE( Coverage );
    OTV_OPTIONAL_TABLE( MKRecordOffset );


    OTV_NAME_ENTER( "MathKernInfo" );

    OTV_LIMIT_CHECK( 4 );

    OTV_OPTIONAL_OFFSET( Coverage );
    cnt = FT_NEXT_USHORT( p );

    OTV_LIMIT_CHECK( 8 * cnt );
    table_size = 4 + 8 * cnt;

    OTV_SIZE_CHECK( Coverage );
    otv_Coverage_validate( table + Coverage, otvalid, (FT_Int)cnt );

    for ( i = 0; i < cnt; i++ )
    {
      for ( j = 0; j < 4; j++ )
      {
        OTV_OPTIONAL_OFFSET( MKRecordOffset );
        OTV_SIZE_CHECK( MKRecordOffset );
        if ( MKRecordOffset )
          otv_MathKern_validate( table + MKRecordOffset, otvalid );
      }
    }

    OTV_EXIT;
  }