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
struct TYPE_3__ {int /*<<< orphan*/  id; scalar_t__ instance; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int unit_name_path_unescape (scalar_t__,char**) ; 
 int unit_name_to_path (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int specifier_filename(char specifier, const void *data, const void *userdata, char **ret) {
        const Unit *u = userdata;

        assert(u);

        if (u->instance)
                return unit_name_path_unescape(u->instance, ret);
        else
                return unit_name_to_path(u->id, ret);
}