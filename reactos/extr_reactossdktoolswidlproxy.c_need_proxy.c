#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DISPINTERFACE ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object (TYPE_1__ const*) ; 

int need_proxy(const type_t *iface)
{
    if (!is_object( iface )) return 0;
    if (is_local( iface->attrs )) return 0;
    if (is_attr( iface->attrs, ATTR_DISPINTERFACE )) return 0;
    return 1;
}