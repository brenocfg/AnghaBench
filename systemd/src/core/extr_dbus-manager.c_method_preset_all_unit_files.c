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
typedef  scalar_t__ UnitFilePresetMode ;
typedef  int /*<<< orphan*/  UnitFileFlags ;
typedef  int /*<<< orphan*/  UnitFileChange ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNIT_FILE_PRESET_FULL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_manage_unit_files_async (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int install_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ isempty (char const*) ; 
 int mac_selinux_access_check (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int reply_unit_file_changes_and_free (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,int*,int*) ; 
 int /*<<< orphan*/  unit_file_bools_to_flags (int,int) ; 
 int unit_file_preset_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ unit_file_preset_mode_from_string (char const*) ; 

__attribute__((used)) static int method_preset_all_unit_files(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        UnitFileChange *changes = NULL;
        size_t n_changes = 0;
        Manager *m = userdata;
        UnitFilePresetMode mm;
        const char *mode;
        UnitFileFlags flags;
        int force, runtime, r;

        assert(message);
        assert(m);

        r = mac_selinux_access_check(message, "enable", error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "sbb", &mode, &runtime, &force);
        if (r < 0)
                return r;

        flags = unit_file_bools_to_flags(runtime, force);

        if (isempty(mode))
                mm = UNIT_FILE_PRESET_FULL;
        else {
                mm = unit_file_preset_mode_from_string(mode);
                if (mm < 0)
                        return -EINVAL;
        }

        r = bus_verify_manage_unit_files_async(m, message, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        r = unit_file_preset_all(m->unit_file_scope, flags, NULL, mm, &changes, &n_changes);
        if (r < 0)
                return install_error(error, r, changes, n_changes);

        return reply_unit_file_changes_and_free(m, message, -1, changes, n_changes, error);
}