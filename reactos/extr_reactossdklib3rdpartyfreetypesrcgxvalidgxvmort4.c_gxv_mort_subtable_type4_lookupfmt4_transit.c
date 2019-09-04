#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  u; } ;
struct TYPE_7__ {int lookuptbl_head; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  TYPE_2__ GXV_LookupValueDesc ;
typedef  TYPE_3__* GXV_LookupValueCPtr ;
typedef  int FT_UShort ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static GXV_LookupValueDesc
  gxv_mort_subtable_type4_lookupfmt4_transit(
    FT_UShort            relative_gindex,
    GXV_LookupValueCPtr  base_value_p,
    FT_Bytes             lookuptbl_limit,
    GXV_Validator        gxvalid )
  {
    FT_Bytes             p;
    FT_Bytes             limit;
    FT_UShort            offset;
    GXV_LookupValueDesc  value;

    /* XXX: check range? */
    offset = (FT_UShort)( base_value_p->u +
                          relative_gindex * sizeof ( FT_UShort ) );

    p     = gxvalid->lookuptbl_head + offset;
    limit = lookuptbl_limit;

    GXV_LIMIT_CHECK( 2 );
    value.u = FT_NEXT_USHORT( p );

    return value;
  }