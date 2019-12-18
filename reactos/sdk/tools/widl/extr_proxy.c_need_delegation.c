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
struct TYPE_5__ {int /*<<< orphan*/  attrs; scalar_t__ ignore; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 scalar_t__ is_local (int /*<<< orphan*/ ) ; 
 TYPE_1__* type_iface_get_inherit (TYPE_1__ const*) ; 

__attribute__((used)) static int need_delegation(const type_t *iface)
{
    const type_t *parent = type_iface_get_inherit( iface );
    return parent && type_iface_get_inherit(parent) && (parent->ignore || is_local( parent->attrs ));
}