#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  subtable_length; TYPE_1__* root; } ;
struct TYPE_9__ {scalar_t__ base; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  scalar_t__ FT_UShort ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 scalar_t__ FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_ODTECT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_ODTECT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_just_justClassTable_validate (scalar_t__,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  gxv_just_justData_lookuptable_validate (scalar_t__,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  gxv_just_postcompTable_validate (scalar_t__,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  gxv_just_widthDeltaClusters_validate (scalar_t__,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  gxv_odtect_add_range (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_odtect_validate (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  odtect ; 

__attribute__((used)) static void
  gxv_just_justData_validate( FT_Bytes       table,
                              FT_Bytes       limit,
                              GXV_Validator  gxvalid )
  {
    /*
     * following 3 offsets are measured from the start of `just'
     * (which table points to), not justData
     */
    FT_UShort  justClassTableOffset;
    FT_UShort  wdcTableOffset;
    FT_UShort  pcTableOffset;
    FT_Bytes   p = table;

    GXV_ODTECT( 4, odtect );


    GXV_NAME_ENTER( "just justData" );

    GXV_ODTECT_INIT( odtect );
    GXV_LIMIT_CHECK( 2 + 2 + 2 );
    justClassTableOffset = FT_NEXT_USHORT( p );
    wdcTableOffset       = FT_NEXT_USHORT( p );
    pcTableOffset        = FT_NEXT_USHORT( p );

    GXV_TRACE(( " (justClassTableOffset = 0x%04x)\n", justClassTableOffset ));
    GXV_TRACE(( " (wdcTableOffset = 0x%04x)\n", wdcTableOffset ));
    GXV_TRACE(( " (pcTableOffset = 0x%04x)\n", pcTableOffset ));

    gxv_just_justData_lookuptable_validate( p, limit, gxvalid );
    gxv_odtect_add_range( p, gxvalid->subtable_length,
                          "just_LookupTable", odtect );

    if ( wdcTableOffset )
    {
      gxv_just_widthDeltaClusters_validate(
        gxvalid->root->base + wdcTableOffset, limit, gxvalid );
      gxv_odtect_add_range( gxvalid->root->base + wdcTableOffset,
                            gxvalid->subtable_length, "just_wdcTable", odtect );
    }

    if ( pcTableOffset )
    {
      gxv_just_postcompTable_validate( gxvalid->root->base + pcTableOffset,
                                       limit, gxvalid );
      gxv_odtect_add_range( gxvalid->root->base + pcTableOffset,
                            gxvalid->subtable_length, "just_pcTable", odtect );
    }

    if ( justClassTableOffset )
    {
      gxv_just_justClassTable_validate(
        gxvalid->root->base + justClassTableOffset, limit, gxvalid );
      gxv_odtect_add_range( gxvalid->root->base + justClassTableOffset,
                            gxvalid->subtable_length, "just_justClassTable",
                            odtect );
    }

    gxv_odtect_validate( odtect, gxvalid );

    GXV_EXIT;
  }