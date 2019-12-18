#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_2__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOTTY ; 
 int /*<<< orphan*/  FILE_SIZE_VALID_OR_INFINITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_qgroup_set_limit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_subvol_set_subtree_quota_limit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_verify_polkit_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int,char*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int setup_machine_directory (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_set_pool_limit(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        uint64_t limit;
        int r;

        assert(message);

        r = sd_bus_message_read(message, "t", &limit);
        if (r < 0)
                return r;
        if (!FILE_SIZE_VALID_OR_INFINITY(limit))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "New limit out of range");

        r = bus_verify_polkit_async(
                        message,
                        CAP_SYS_ADMIN,
                        "org.freedesktop.machine1.manage-machines",
                        NULL,
                        false,
                        UID_INVALID,
                        &m->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Will call us back */

        /* Set up the machine directory if necessary */
        r = setup_machine_directory(error);
        if (r < 0)
                return r;

        (void) btrfs_qgroup_set_limit("/var/lib/machines", 0, limit);

        r = btrfs_subvol_set_subtree_quota_limit("/var/lib/machines", 0, limit);
        if (r == -ENOTTY)
                return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Quota is only supported on btrfs.");
        if (r < 0)
                return sd_bus_error_set_errnof(error, r, "Failed to adjust quota limit: %m");

        return sd_bus_reply_method_return(message, NULL);
}