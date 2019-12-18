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
struct TYPE_3__ {size_t u; } ;
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  TYPE_1__* GXV_LookupValueCPtr ;
typedef  size_t FT_UShort ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_UNUSED (size_t) ; 
 scalar_t__ GXV_BSLN_DATA (int /*<<< orphan*/ ) ; 
 size_t GXV_BSLN_VALUE_COUNT ; 
 size_t GXV_BSLN_VALUE_EMPTY ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  ctlPoints_p ; 

__attribute__((used)) static void
  gxv_bsln_LookupValue_validate( FT_UShort            glyph,
                                 GXV_LookupValueCPtr  value_p,
                                 GXV_Validator        gxvalid )
  {
    FT_UShort     v = value_p->u;
    FT_UShort*    ctlPoints;

    FT_UNUSED( glyph );


    GXV_NAME_ENTER( "lookup value" );

    if ( v >= GXV_BSLN_VALUE_COUNT )
      FT_INVALID_DATA;

    ctlPoints = (FT_UShort*)GXV_BSLN_DATA( ctlPoints_p );
    if ( ctlPoints && ctlPoints[v] == GXV_BSLN_VALUE_EMPTY )
      FT_INVALID_DATA;

    GXV_EXIT;
  }