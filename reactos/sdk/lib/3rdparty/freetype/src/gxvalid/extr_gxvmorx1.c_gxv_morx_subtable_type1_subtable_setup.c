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
struct TYPE_8__ {TYPE_1__ xstatetable; } ;
struct TYPE_7__ {int /*<<< orphan*/  substitutionTable_length; int /*<<< orphan*/  substitutionTable; } ;
typedef  TYPE_2__* GXV_morx_subtable_type1_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  int /*<<< orphan*/  FT_ULong ;

/* Variables and functions */
 int /*<<< orphan*/  gxv_set_length_by_ulong_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
  gxv_morx_subtable_type1_subtable_setup( FT_ULong       table_size,
                                          FT_ULong       classTable,
                                          FT_ULong       stateArray,
                                          FT_ULong       entryTable,
                                          FT_ULong*      classTable_length_p,
                                          FT_ULong*      stateArray_length_p,
                                          FT_ULong*      entryTable_length_p,
                                          GXV_Validator  gxvalid )
  {
    FT_ULong  o[4];
    FT_ULong  *l[4];
    FT_ULong  buff[5];

    GXV_morx_subtable_type1_StateOptRecData  optdata =
      (GXV_morx_subtable_type1_StateOptRecData)gxvalid->xstatetable.optdata;


    o[0] = classTable;
    o[1] = stateArray;
    o[2] = entryTable;
    o[3] = optdata->substitutionTable;
    l[0] = classTable_length_p;
    l[1] = stateArray_length_p;
    l[2] = entryTable_length_p;
    l[3] = &(optdata->substitutionTable_length);

    gxv_set_length_by_ulong_offset( o, l, buff, 4, table_size, gxvalid );
  }