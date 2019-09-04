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
struct TYPE_4__ {int /*<<< orphan*/  glyph_count; int /*<<< orphan*/  extra1; } ;
typedef  TYPE_1__* OTV_Validator ;
typedef  int FT_UInt ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int DefJstfLangSys ; 
 int ExtGlyph ; 
 int /*<<< orphan*/  ExtenderGlyph ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  JstfLangSys ; 
 int /*<<< orphan*/  JstfPriority ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_NEST1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_NEST2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_RUN (int,TYPE_1__*) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 

__attribute__((used)) static void
  otv_JstfScript_validate( FT_Bytes       table,
                           OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   table_size;
    FT_UInt   JstfLangSysCount;

    OTV_OPTIONAL_TABLE( ExtGlyph );
    OTV_OPTIONAL_TABLE( DefJstfLangSys );


    OTV_NAME_ENTER( "JstfScript" );

    OTV_LIMIT_CHECK( 6 );
    OTV_OPTIONAL_OFFSET( ExtGlyph );
    OTV_OPTIONAL_OFFSET( DefJstfLangSys );
    JstfLangSysCount = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (JstfLangSysCount = %d)\n", JstfLangSysCount ));

    table_size = JstfLangSysCount * 6 + 6;

    OTV_SIZE_CHECK( ExtGlyph );
    if ( ExtGlyph )
    {
      otvalid->extra1 = otvalid->glyph_count;
      OTV_NEST1( ExtenderGlyph );
      OTV_RUN( table + ExtGlyph, otvalid );
    }

    OTV_SIZE_CHECK( DefJstfLangSys );
    if ( DefJstfLangSys )
    {
      OTV_NEST2( JstfLangSys, JstfPriority );
      OTV_RUN( table + DefJstfLangSys, otvalid );
    }

    OTV_LIMIT_CHECK( 6 * JstfLangSysCount );

    /* JstfLangSysRecord */
    OTV_NEST2( JstfLangSys, JstfPriority );
    for ( ; JstfLangSysCount > 0; JstfLangSysCount-- )
    {
      p += 4;       /* skip JstfLangSysTag */

      OTV_RUN( table + FT_NEXT_USHORT( p ), otvalid );
    }

    OTV_EXIT;
  }