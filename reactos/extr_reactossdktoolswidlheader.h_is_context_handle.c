#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CONTEXTHANDLE ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr (TYPE_1__ const*) ; 
 TYPE_1__* type_alias_get_aliasee (TYPE_1__ const*) ; 
 scalar_t__ type_is_alias (TYPE_1__ const*) ; 
 TYPE_1__* type_pointer_get_ref (TYPE_1__ const*) ; 

__attribute__((used)) static inline int is_context_handle(const type_t *type)
{
    const type_t *t;
    for (t = type;
         is_ptr(t) || type_is_alias(t);
         t = type_is_alias(t) ? type_alias_get_aliasee(t) : type_pointer_get_ref(t))
        if (is_attr(t->attrs, ATTR_CONTEXTHANDLE))
            return 1;
    return 0;
}