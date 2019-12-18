#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  int FT_UShort ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  GXV_EXIT ; 
 int GXV_KERN_SUBTABLE_HEADER_SIZE ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  gxv_BinSrchHeader_validate (int,int,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_kern_subtable_fmt0_pairs_validate (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_kern_subtable_fmt0_validate( FT_Bytes       table,
                                   FT_Bytes       limit,
                                   GXV_Validator  gxvalid )
  {
    FT_Bytes   p = table + GXV_KERN_SUBTABLE_HEADER_SIZE;

    FT_UShort  nPairs;
    FT_UShort  unitSize;


    GXV_NAME_ENTER( "kern subtable format 0" );

    unitSize = 2 + 2 + 2;
    nPairs   = 0;

    /* nPairs, searchRange, entrySelector, rangeShift */
    GXV_LIMIT_CHECK( 2 + 2 + 2 + 2 );
    gxv_BinSrchHeader_validate( p, limit, &unitSize, &nPairs, gxvalid );
    p += 2 + 2 + 2 + 2;

    gxv_kern_subtable_fmt0_pairs_validate( p, limit, nPairs, gxvalid );

    GXV_EXIT;
  }