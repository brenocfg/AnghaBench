#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int glyph_count; } ;
typedef  TYPE_1__* OTV_Validator ;
typedef  int FT_UInt ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_INVALID_FORMAT ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int otv_Coverage_get_count (int) ; 
 int /*<<< orphan*/  otv_Coverage_validate (int,TYPE_1__*,int) ; 

__attribute__((used)) static void
  otv_ReverseChainSingleSubst_validate( FT_Bytes       table,
                                        OTV_Validator  otvalid )
  {
    FT_Bytes  p = table, Coverage;
    FT_UInt   SubstFormat;
    FT_UInt   BacktrackGlyphCount, LookaheadGlyphCount, GlyphCount;


    OTV_NAME_ENTER( "ReverseChainSingleSubst" );

    OTV_LIMIT_CHECK( 2 );
    SubstFormat = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (format %d)\n", SubstFormat ));

    switch ( SubstFormat )
    {
    case 1:     /* ReverseChainSingleSubstFormat1 */
      OTV_LIMIT_CHECK( 4 );
      Coverage            = table + FT_NEXT_USHORT( p );
      BacktrackGlyphCount = FT_NEXT_USHORT( p );

      OTV_TRACE(( " (BacktrackGlyphCount = %d)\n", BacktrackGlyphCount ));

      otv_Coverage_validate( Coverage, otvalid, -1 );

      OTV_LIMIT_CHECK( BacktrackGlyphCount * 2 + 2 );

      for ( ; BacktrackGlyphCount > 0; BacktrackGlyphCount-- )
        otv_Coverage_validate( table + FT_NEXT_USHORT( p ), otvalid, -1 );

      LookaheadGlyphCount = FT_NEXT_USHORT( p );

      OTV_TRACE(( " (LookaheadGlyphCount = %d)\n", LookaheadGlyphCount ));

      OTV_LIMIT_CHECK( LookaheadGlyphCount * 2 + 2 );

      for ( ; LookaheadGlyphCount > 0; LookaheadGlyphCount-- )
        otv_Coverage_validate( table + FT_NEXT_USHORT( p ), otvalid, -1 );

      GlyphCount = FT_NEXT_USHORT( p );

      OTV_TRACE(( " (GlyphCount = %d)\n", GlyphCount ));

      if ( GlyphCount != otv_Coverage_get_count( Coverage ) )
        FT_INVALID_DATA;

      OTV_LIMIT_CHECK( GlyphCount * 2 );

      /* Substitute */
      for ( ; GlyphCount > 0; GlyphCount-- )
        if ( FT_NEXT_USHORT( p ) >= otvalid->glyph_count )
          FT_INVALID_DATA;

      break;

    default:
      FT_INVALID_FORMAT;
    }

    OTV_EXIT;
  }