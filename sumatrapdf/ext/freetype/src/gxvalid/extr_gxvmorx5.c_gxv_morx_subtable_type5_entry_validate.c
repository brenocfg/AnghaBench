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
struct TYPE_3__ {int ul; } ;
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  TYPE_1__* GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  int /*<<< orphan*/  FT_Bytes ;
typedef  scalar_t__ FT_Byte ;
typedef  int /*<<< orphan*/  FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FT_BOOL (int) ; 
 int /*<<< orphan*/  FT_UNUSED (int) ; 
 int /*<<< orphan*/  gxv_morx_subtable_type5_InsertList_validate (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_morx_subtable_type5_entry_validate(
    FT_UShort                       state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    FT_Bool    setMark;
    FT_Bool    dontAdvance;
    FT_Bool    currentIsKashidaLike;
    FT_Bool    markedIsKashidaLike;
    FT_Bool    currentInsertBefore;
    FT_Bool    markedInsertBefore;
#endif
    FT_Byte    currentInsertCount;
    FT_Byte    markedInsertCount;
    FT_Byte    currentInsertList;
    FT_UShort  markedInsertList;

    FT_UNUSED( state );


#ifdef GXV_LOAD_UNUSED_VARS
    setMark              = FT_BOOL( ( flags >> 15 ) & 1 );
    dontAdvance          = FT_BOOL( ( flags >> 14 ) & 1 );
    currentIsKashidaLike = FT_BOOL( ( flags >> 13 ) & 1 );
    markedIsKashidaLike  = FT_BOOL( ( flags >> 12 ) & 1 );
    currentInsertBefore  = FT_BOOL( ( flags >> 11 ) & 1 );
    markedInsertBefore   = FT_BOOL( ( flags >> 10 ) & 1 );
#endif

    currentInsertCount = (FT_Byte)( ( flags >> 5 ) & 0x1F   );
    markedInsertCount  = (FT_Byte)(   flags        & 0x001F );

    currentInsertList = (FT_Byte)  ( glyphOffset_p->ul >> 16 );
    markedInsertList  = (FT_UShort)( glyphOffset_p->ul       );

    if ( currentInsertList && 0 != currentInsertCount )
      gxv_morx_subtable_type5_InsertList_validate( currentInsertList,
                                                   currentInsertCount,
                                                   table, limit,
                                                   gxvalid );

    if ( markedInsertList && 0 != markedInsertCount )
      gxv_morx_subtable_type5_InsertList_validate( markedInsertList,
                                                   markedInsertCount,
                                                   table, limit,
                                                   gxvalid );
  }