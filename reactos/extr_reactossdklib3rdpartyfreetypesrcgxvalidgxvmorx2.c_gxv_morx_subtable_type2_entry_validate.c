#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int u; } ;
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  TYPE_1__* GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_UNUSED (int) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_morx_subtable_type2_ligActionIndex_validate (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_morx_subtable_type2_entry_validate(
    FT_UShort                       state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    FT_UShort  setComponent;
    FT_UShort  dontAdvance;
    FT_UShort  performAction;
#endif
    FT_UShort  reserved;
    FT_UShort  ligActionIndex;

    FT_UNUSED( state );
    FT_UNUSED( limit );


#ifdef GXV_LOAD_UNUSED_VARS
    setComponent   = (FT_UShort)( ( flags >> 15 ) & 1 );
    dontAdvance    = (FT_UShort)( ( flags >> 14 ) & 1 );
    performAction  = (FT_UShort)( ( flags >> 13 ) & 1 );
#endif

    reserved       = (FT_UShort)( flags & 0x1FFF );
    ligActionIndex = glyphOffset_p->u;

    if ( reserved > 0 )
      GXV_TRACE(( "  reserved 14bit is non-zero\n" ));

    if ( 0 < ligActionIndex )
      gxv_morx_subtable_type2_ligActionIndex_validate(
        table, ligActionIndex, gxvalid );
  }