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
struct TYPE_4__ {struct TYPE_4__* symlink_target; struct TYPE_4__* default_instance; int /*<<< orphan*/  also; int /*<<< orphan*/  required_by; int /*<<< orphan*/  wanted_by; int /*<<< orphan*/  aliases; struct TYPE_4__* path; struct TYPE_4__* name; } ;
typedef  TYPE_1__ UnitFileInstallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void install_info_free(UnitFileInstallInfo *i) {

        if (!i)
                return;

        free(i->name);
        free(i->path);
        strv_free(i->aliases);
        strv_free(i->wanted_by);
        strv_free(i->required_by);
        strv_free(i->also);
        free(i->default_instance);
        free(i->symlink_target);
        free(i);
}