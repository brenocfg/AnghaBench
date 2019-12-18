#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 scalar_t__ cg_all_unified () ; 
 char* empty_to_root (char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_cg_info(const char *controller, const char *path) {

        if (cg_all_unified() == 0 && controller && !streq(controller, SYSTEMD_CGROUP_CONTROLLER))
                printf("Controller %s; ", controller);

        printf("Control group %s:\n", empty_to_root(path));
        fflush(stdout);
}