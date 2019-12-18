#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_WIREMARSHAL ; 
 TYPE_1__* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* type_alias_get_aliasee (TYPE_1__ const*) ; 
 scalar_t__ type_is_alias (TYPE_1__ const*) ; 

__attribute__((used)) static type_t *get_user_type(const type_t *t, const char **pname)
{
    for (;;)
    {
        type_t *ut = get_attrp(t->attrs, ATTR_WIREMARSHAL);
        if (ut)
        {
            if (pname)
                *pname = t->name;
            return ut;
        }

        if (type_is_alias(t))
            t = type_alias_get_aliasee(t);
        else
            return NULL;
    }
}