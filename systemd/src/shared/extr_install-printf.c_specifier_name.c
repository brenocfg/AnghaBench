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
struct TYPE_3__ {int /*<<< orphan*/  name; scalar_t__ default_instance; } ;
typedef  TYPE_1__ UnitFileInstallInfo ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  UNIT_NAME_TEMPLATE ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ unit_name_is_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unit_name_replace_instance (int /*<<< orphan*/ ,scalar_t__,char**) ; 

__attribute__((used)) static int specifier_name(char specifier, const void *data, const void *userdata, char **ret) {
        const UnitFileInstallInfo *i = userdata;
        char *ans;

        assert(i);

        if (unit_name_is_valid(i->name, UNIT_NAME_TEMPLATE) && i->default_instance)
                return unit_name_replace_instance(i->name, i->default_instance, ret);

        ans = strdup(i->name);
        if (!ans)
                return -ENOMEM;
        *ret = ans;
        return 0;
}