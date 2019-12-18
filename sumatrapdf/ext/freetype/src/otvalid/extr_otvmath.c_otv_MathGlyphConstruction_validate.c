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
 int /*<<< orphan*/  FT_INVALID_GLYPH_ID ; 
 int FT_NEXT_USHORT (int) ; 
 int GlyphAssembly ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  otv_GlyphAssembly_validate (int,TYPE_1__*) ; 

__attribute__((used)) static void
  otv_MathGlyphConstruction_validate( FT_Bytes       table,
                                      OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   vcnt, table_size;
    FT_UInt   i;

    OTV_OPTIONAL_TABLE( GlyphAssembly );


    /* OTV_NAME_ENTER( "MathGlyphConstruction" ); */

    OTV_LIMIT_CHECK( 4 );

    OTV_OPTIONAL_OFFSET( GlyphAssembly );
    vcnt = FT_NEXT_USHORT( p );

    OTV_LIMIT_CHECK( 4 * vcnt );
    table_size = 4 + 4 * vcnt;

    for ( i = 0; i < vcnt; i++ )
    {
      FT_UInt  gid;


      gid = FT_NEXT_USHORT( p );
      if ( gid >= otvalid->glyph_count )
        FT_INVALID_GLYPH_ID;
      p += 2;                          /* skip the size */
    }

    OTV_SIZE_CHECK( GlyphAssembly );
    if ( GlyphAssembly )
      otv_GlyphAssembly_validate( table+GlyphAssembly, otvalid );

    /* OTV_EXIT; */
  }