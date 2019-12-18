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
struct machine_info {int dummy; } ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_MANAGER ; 
 int acquire_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  arg_pager_flags ; 
 int /*<<< orphan*/  compare_machine_info ; 
 int /*<<< orphan*/  free_machines_list (struct machine_info*,int) ; 
 int get_machine_list (int /*<<< orphan*/ *,struct machine_info**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_machines_list (struct machine_info*,int) ; 
 int /*<<< orphan*/  pager_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_skip (char**,int) ; 
 int /*<<< orphan*/  typesafe_qsort (struct machine_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int list_machines(int argc, char *argv[], void *userdata) {
        struct machine_info *machine_infos = NULL;
        sd_bus *bus;
        int r;

        r = acquire_bus(BUS_MANAGER, &bus);
        if (r < 0)
                return r;

        r = get_machine_list(bus, &machine_infos, strv_skip(argv, 1));
        if (r < 0)
                return r;

        (void) pager_open(arg_pager_flags);

        typesafe_qsort(machine_infos, r, compare_machine_info);
        output_machines_list(machine_infos, r);
        free_machines_list(machine_infos, r);

        return 0;
}