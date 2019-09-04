#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lcid2; int /*<<< orphan*/  lcid; } ;
struct TYPE_9__ {TYPE_2__ typelib_header; TYPE_1__* typelib; } ;
typedef  TYPE_3__ msft_typelib_t ;
struct TYPE_10__ {int /*<<< orphan*/  cval; } ;
typedef  TYPE_4__ expr_t ;
struct TYPE_7__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_LIBLCID ; 
 TYPE_4__* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_lcid(msft_typelib_t *typelib)
{
    const expr_t *lcid_expr = get_attrp( typelib->typelib->attrs, ATTR_LIBLCID );
    if(lcid_expr)
    {
        typelib->typelib_header.lcid  = lcid_expr->cval;
        typelib->typelib_header.lcid2 = lcid_expr->cval;
    }
}