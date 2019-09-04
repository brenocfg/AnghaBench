#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ subtable_length; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  scalar_t__ FT_ULong ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  gxv_just_pcActionRecord_validate (scalar_t__,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_just_pcLookupTable_validate (scalar_t__,scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static void
  gxv_just_postcompTable_validate( FT_Bytes       table,
                                   FT_Bytes       limit,
                                   GXV_Validator  gxvalid )
  {
    FT_Bytes  p = table;


    GXV_NAME_ENTER( "just postcompTable" );

    gxv_just_pcLookupTable_validate( p, limit, gxvalid );
    p += gxvalid->subtable_length;

    gxv_just_pcActionRecord_validate( p, limit, gxvalid );
    p += gxvalid->subtable_length;

    gxvalid->subtable_length = (FT_ULong)( p - table );

    GXV_EXIT;
  }