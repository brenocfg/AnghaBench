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
struct TYPE_3__ {int /*<<< orphan*/  u; } ;
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  TYPE_1__* GXV_LookupValueCPtr ;
typedef  int /*<<< orphan*/  FT_UShort ;

/* Variables and functions */
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_glyphid_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type4_lookupval_validate( FT_UShort            glyph,
                                              GXV_LookupValueCPtr  value_p,
                                              GXV_Validator        gxvalid )
  {
    FT_UNUSED( glyph );

    gxv_glyphid_validate( value_p->u, gxvalid );
  }