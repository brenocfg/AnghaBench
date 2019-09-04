#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ optdata; } ;
struct TYPE_9__ {int min_gid; int max_gid; TYPE_2__* face; TYPE_1__ statetable; } ;
struct TYPE_8__ {int substitutionTable; scalar_t__ substitutionTable_length; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_glyphs; } ;
typedef  TYPE_3__ GXV_mort_subtable_type1_StateOptRec ;
typedef  TYPE_4__* GXV_Validator ;
typedef  int FT_UShort ;
typedef  int /*<<< orphan*/  FT_String ;
typedef  int FT_Short ;
typedef  int /*<<< orphan*/  const* FT_Byte ;

/* Variables and functions */
 scalar_t__ FT_MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type1_offset_to_subst_validate(
    FT_Short          wordOffset,
    const FT_String*  tag,
    FT_Byte           state,
    GXV_Validator     gxvalid )
  {
    FT_UShort  substTable;
    FT_UShort  substTable_limit;

    FT_UNUSED( tag );
    FT_UNUSED( state );


    substTable =
      ((GXV_mort_subtable_type1_StateOptRec *)
       (gxvalid->statetable.optdata))->substitutionTable;
    substTable_limit =
      (FT_UShort)( substTable +
                   ((GXV_mort_subtable_type1_StateOptRec *)
                    (gxvalid->statetable.optdata))->substitutionTable_length );

    gxvalid->min_gid = (FT_UShort)( ( substTable       - wordOffset * 2 ) / 2 );
    gxvalid->max_gid = (FT_UShort)( ( substTable_limit - wordOffset * 2 ) / 2 );
    gxvalid->max_gid = (FT_UShort)( FT_MAX( gxvalid->max_gid,
                                            gxvalid->face->num_glyphs ) );

    /* XXX: check range? */

    /* TODO: min_gid & max_gid comparison with ClassTable contents */
  }