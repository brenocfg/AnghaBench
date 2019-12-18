#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  entry_validate_func; int /*<<< orphan*/  entry_glyphoffset_fmt; int /*<<< orphan*/ * subtable_setup_func; int /*<<< orphan*/ * optdata_load_func; int /*<<< orphan*/ * optdata; } ;
struct TYPE_6__ {TYPE_1__ statetable; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  int FT_UShort ;
typedef  scalar_t__ FT_ULong ;
typedef  int FT_Bytes ;

/* Variables and functions */
 scalar_t__ FT_NEXT_ULONG (int) ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_GLYPHOFFSET_NONE ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_StateTable_validate (int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  gxv_just_classTable_entry_validate ; 

__attribute__((used)) static void
  gxv_just_justClassTable_validate ( FT_Bytes       table,
                                     FT_Bytes       limit,
                                     GXV_Validator  gxvalid )
  {
    FT_Bytes   p = table;
    FT_UShort  length;
    FT_UShort  coverage;
    FT_ULong   subFeatureFlags;


    GXV_NAME_ENTER( "just justClassTable" );

    GXV_LIMIT_CHECK( 2 + 2 + 4 );
    length          = FT_NEXT_USHORT( p );
    coverage        = FT_NEXT_USHORT( p );
    subFeatureFlags = FT_NEXT_ULONG( p );

    GXV_TRACE(( "  justClassTable: coverage = 0x%04x (%s) ", coverage ));
    if ( ( coverage & 0x4000 ) == 0  )
      GXV_TRACE(( "ascending\n" ));
    else
      GXV_TRACE(( "descending\n" ));

    if ( subFeatureFlags )
      GXV_TRACE(( "  justClassTable: nonzero value (0x%08x)"
                  " in unused subFeatureFlags\n", subFeatureFlags ));

    gxvalid->statetable.optdata               = NULL;
    gxvalid->statetable.optdata_load_func     = NULL;
    gxvalid->statetable.subtable_setup_func   = NULL;
    gxvalid->statetable.entry_glyphoffset_fmt = GXV_GLYPHOFFSET_NONE;
    gxvalid->statetable.entry_validate_func   =
      gxv_just_classTable_entry_validate;

    gxv_StateTable_validate( p, table + length, gxvalid );

    /* subtable_length is set by gxv_LookupTable_validate() */

    GXV_EXIT;
  }