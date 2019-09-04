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
struct TYPE_4__ {struct TYPE_4__* orig; scalar_t__ is_alias; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */

__attribute__((used)) static inline type_t *type_get_real_type(const type_t *type)
{
    if (type->is_alias)
        return type_get_real_type(type->orig);
    else
        return (type_t *)type;
}