#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  unit_file_scope; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  UnitFileChange ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_FILE_FORCE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_manage_unit_files_async (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int install_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 int mac_selinux_access_check (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int reply_unit_file_changes_and_free (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,int*) ; 
 int unit_file_set_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static int method_set_default_target(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        UnitFileChange *changes = NULL;
        size_t n_changes = 0;
        Manager *m = userdata;
        const char *name;
        int force, r;

        assert(message);
        assert(m);

        r = mac_selinux_access_check(message, "enable", error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "sb", &name, &force);
        if (r < 0)
                return r;

        r = bus_verify_manage_unit_files_async(m, message, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        r = unit_file_set_default(m->unit_file_scope, force ? UNIT_FILE_FORCE : 0, NULL, name, &changes, &n_changes);
        if (r < 0)
                return install_error(error, r, changes, n_changes);

        return reply_unit_file_changes_and_free(m, message, -1, changes, n_changes, error);
}