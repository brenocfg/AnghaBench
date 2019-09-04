#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ul; } ;
struct TYPE_7__ {int /*<<< orphan*/  optdata; } ;
struct TYPE_9__ {TYPE_1__ xstatetable; } ;
struct TYPE_8__ {scalar_t__ substitutionTable_num_lookupTables; } ;
typedef  TYPE_2__* GXV_morx_subtable_type1_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  TYPE_4__* GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  scalar_t__ FT_Short ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_UNUSED (int) ; 
 int /*<<< orphan*/  GXV_SET_ERR_IF_PARANOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  dontAdvance ; 
 int /*<<< orphan*/  setMark ; 

__attribute__((used)) static void
  gxv_morx_subtable_type1_entry_validate(
    FT_UShort                       state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_TRACE_VARS
    FT_UShort  setMark;
    FT_UShort  dontAdvance;
#endif
    FT_UShort  reserved;
    FT_Short   markIndex;
    FT_Short   currentIndex;

    GXV_morx_subtable_type1_StateOptRecData  optdata =
      (GXV_morx_subtable_type1_StateOptRecData)gxvalid->xstatetable.optdata;

    FT_UNUSED( state );
    FT_UNUSED( table );
    FT_UNUSED( limit );


#ifdef GXV_LOAD_TRACE_VARS
    setMark      = (FT_UShort)( ( flags >> 15 ) & 1 );
    dontAdvance  = (FT_UShort)( ( flags >> 14 ) & 1 );
#endif

    reserved = (FT_UShort)( flags & 0x3FFF );

    markIndex    = (FT_Short)( glyphOffset_p->ul >> 16 );
    currentIndex = (FT_Short)( glyphOffset_p->ul       );

    GXV_TRACE(( " setMark=%01d dontAdvance=%01d\n",
                setMark, dontAdvance ));

    if ( 0 < reserved )
    {
      GXV_TRACE(( " non-zero bits found in reserved range\n" ));
      GXV_SET_ERR_IF_PARANOID( FT_INVALID_DATA );
    }

    GXV_TRACE(( "markIndex = %d, currentIndex = %d\n",
                markIndex, currentIndex ));

    if ( optdata->substitutionTable_num_lookupTables < markIndex + 1 )
      optdata->substitutionTable_num_lookupTables =
        (FT_UShort)( markIndex + 1 );

    if ( optdata->substitutionTable_num_lookupTables < currentIndex + 1 )
      optdata->substitutionTable_num_lookupTables =
        (FT_UShort)( currentIndex + 1 );
  }