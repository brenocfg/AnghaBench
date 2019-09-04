#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  optdata; } ;
struct TYPE_8__ {int /*<<< orphan*/  lookupfmt4_trans; int /*<<< orphan*/  lookupval_func; int /*<<< orphan*/  lookupval_sign; TYPE_1__ xstatetable; } ;
struct TYPE_7__ {scalar_t__ substitutionTable_num_lookupTables; } ;
typedef  TYPE_2__* GXV_morx_subtable_type1_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  scalar_t__ FT_UShort ;
typedef  scalar_t__ FT_ULong ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 scalar_t__ FT_NEXT_ULONG (scalar_t__) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_LOOKUPVALUE_UNSIGNED ; 
 int /*<<< orphan*/  gxv_LookupTable_validate (scalar_t__,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  gxv_morx_subtable_type1_LookupFmt4_transit ; 
 int /*<<< orphan*/  gxv_morx_subtable_type1_LookupValue_validate ; 

__attribute__((used)) static void
  gxv_morx_subtable_type1_substitutionTable_validate( FT_Bytes       table,
                                                      FT_Bytes       limit,
                                                      GXV_Validator  gxvalid )
  {
    FT_Bytes   p = table;
    FT_UShort  i;

    GXV_morx_subtable_type1_StateOptRecData  optdata =
      (GXV_morx_subtable_type1_StateOptRecData)gxvalid->xstatetable.optdata;


    /* TODO: calculate offset/length for each lookupTables */
    gxvalid->lookupval_sign   = GXV_LOOKUPVALUE_UNSIGNED;
    gxvalid->lookupval_func   = gxv_morx_subtable_type1_LookupValue_validate;
    gxvalid->lookupfmt4_trans = gxv_morx_subtable_type1_LookupFmt4_transit;

    for ( i = 0; i < optdata->substitutionTable_num_lookupTables; i++ )
    {
      FT_ULong  offset;


      GXV_LIMIT_CHECK( 4 );
      offset = FT_NEXT_ULONG( p );

      gxv_LookupTable_validate( table + offset, limit, gxvalid );
    }

    /* TODO: overlapping of lookupTables in substitutionTable */
  }