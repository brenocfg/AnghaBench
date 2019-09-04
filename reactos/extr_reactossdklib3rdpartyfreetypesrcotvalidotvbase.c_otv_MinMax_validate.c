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
typedef  int FT_Bytes ;

/* Variables and functions */
 int FT_NEXT_USHORT (int) ; 
 int MaxCoord ; 
 int MinCoord ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int /*<<< orphan*/  otv_BaseCoord_validate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_MinMax_validate( FT_Bytes       table,
                       OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   table_size;
    FT_UInt   FeatMinMaxCount;

    OTV_OPTIONAL_TABLE( MinCoord );
    OTV_OPTIONAL_TABLE( MaxCoord );


    OTV_NAME_ENTER( "MinMax" );

    OTV_LIMIT_CHECK( 6 );

    OTV_OPTIONAL_OFFSET( MinCoord );
    OTV_OPTIONAL_OFFSET( MaxCoord );
    FeatMinMaxCount = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (FeatMinMaxCount = %d)\n", FeatMinMaxCount ));

    table_size = FeatMinMaxCount * 8 + 6;

    OTV_SIZE_CHECK( MinCoord );
    if ( MinCoord )
      otv_BaseCoord_validate( table + MinCoord, otvalid );

    OTV_SIZE_CHECK( MaxCoord );
    if ( MaxCoord )
      otv_BaseCoord_validate( table + MaxCoord, otvalid );

    OTV_LIMIT_CHECK( FeatMinMaxCount * 8 );

    /* FeatMinMaxRecord */
    for ( ; FeatMinMaxCount > 0; FeatMinMaxCount-- )
    {
      p += 4;                           /* skip FeatureTableTag */

      OTV_OPTIONAL_OFFSET( MinCoord );
      OTV_OPTIONAL_OFFSET( MaxCoord );

      OTV_SIZE_CHECK( MinCoord );
      if ( MinCoord )
        otv_BaseCoord_validate( table + MinCoord, otvalid );

      OTV_SIZE_CHECK( MaxCoord );
      if ( MaxCoord )
        otv_BaseCoord_validate( table + MaxCoord, otvalid );
    }

    OTV_EXIT;
  }