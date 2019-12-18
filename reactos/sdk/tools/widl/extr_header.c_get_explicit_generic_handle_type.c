#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* type; } ;
typedef  TYPE_1__ var_t ;
struct TYPE_14__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_HANDLE ; 
 scalar_t__ TYPE_BASIC ; 
 scalar_t__ TYPE_BASIC_HANDLE ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr (TYPE_2__ const*) ; 
 TYPE_2__* type_alias_get_aliasee (TYPE_2__ const*) ; 
 scalar_t__ type_basic_get_type (TYPE_2__ const*) ; 
 scalar_t__ type_get_type_detect_alias (TYPE_2__ const*) ; 
 scalar_t__ type_is_alias (TYPE_2__ const*) ; 
 TYPE_2__* type_pointer_get_ref (TYPE_2__ const*) ; 

const type_t* get_explicit_generic_handle_type(const var_t* var)
{
    const type_t *t;
    for (t = var->type;
         is_ptr(t) || type_is_alias(t);
         t = type_is_alias(t) ? type_alias_get_aliasee(t) : type_pointer_get_ref(t))
        if ((type_get_type_detect_alias(t) != TYPE_BASIC || type_basic_get_type(t) != TYPE_BASIC_HANDLE) &&
            is_attr(t->attrs, ATTR_HANDLE))
            return t;
    return NULL;
}