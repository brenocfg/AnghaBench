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
 int FT_NEXT_ULONG (int) ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int /*<<< orphan*/  otv_Coverage_validate (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
  otv_MarkGlyphSets_validate( FT_Bytes       table,
                              OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   MarkGlyphSetCount;


    OTV_NAME_ENTER( "MarkGlyphSets" );

    p += 2;     /* skip Format */

    OTV_LIMIT_CHECK( 2 );
    MarkGlyphSetCount = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (MarkGlyphSetCount = %d)\n", MarkGlyphSetCount ));

    OTV_LIMIT_CHECK( MarkGlyphSetCount * 4 );      /* CoverageOffsets */

    for ( ; MarkGlyphSetCount > 0; MarkGlyphSetCount-- )
      otv_Coverage_validate( table + FT_NEXT_ULONG( p ), otvalid, -1 );

    OTV_EXIT;
  }