#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  const* attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_POINTERTYPE ; 
 unsigned char FC_RP ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_attrv (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_array (TYPE_1__ const*) ; 
 scalar_t__ is_ptr (TYPE_1__ const*) ; 
 TYPE_1__* type_alias_get_aliasee (TYPE_1__ const*) ; 
 unsigned char type_array_get_ptr_default_fc (TYPE_1__ const*) ; 
 scalar_t__ type_is_alias (TYPE_1__ const*) ; 
 unsigned char type_pointer_get_default_fc (TYPE_1__ const*) ; 

unsigned char get_pointer_fc(const type_t *type, const attr_list_t *attrs, int toplevel_param)
{
    const type_t *t;
    int pointer_type;

    assert(is_ptr(type) || is_array(type));

    pointer_type = get_attrv(attrs, ATTR_POINTERTYPE);
    if (pointer_type)
        return pointer_type;

    for (t = type; type_is_alias(t); t = type_alias_get_aliasee(t))
    {
        pointer_type = get_attrv(t->attrs, ATTR_POINTERTYPE);
        if (pointer_type)
            return pointer_type;
    }

    if (toplevel_param)
        return FC_RP;
    else if (is_ptr(type))
        return type_pointer_get_default_fc(type);
    else
        return type_array_get_ptr_default_fc(type);
}