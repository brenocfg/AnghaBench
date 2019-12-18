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
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ read_only; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ CustomMount ;

/* Variables and functions */
 scalar_t__ CUSTOM_MOUNT_BIND ; 
 int ENOENT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_log_create_error (int) ; 
 int is_device_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,...) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,...) ; 

__attribute__((used)) static int append_machine_properties(
                sd_bus_message *m,
                CustomMount *mounts,
                unsigned n_mounts,
                int kill_signal) {

        unsigned j;
        int r;

        assert(m);

        r = sd_bus_message_append(m, "(sv)", "DevicePolicy", "s", "closed");
        if (r < 0)
                return bus_log_create_error(r);

        /* If you make changes here, also make sure to update systemd-nspawn@.service, to keep the device policies in
         * sync regardless if we are run with or without the --keep-unit switch. */
        r = sd_bus_message_append(m, "(sv)", "DeviceAllow", "a(ss)", 2,
                                  /* Allow the container to
                                   * access and create the API
                                   * device nodes, so that
                                   * PrivateDevices= in the
                                   * container can work
                                   * fine */
                                  "/dev/net/tun", "rwm",
                                  /* Allow the container
                                   * access to ptys. However,
                                   * do not permit the
                                   * container to ever create
                                   * these device nodes. */
                                  "char-pts", "rw");
        if (r < 0)
                return bus_log_create_error(r);

        for (j = 0; j < n_mounts; j++) {
                CustomMount *cm = mounts + j;

                if (cm->type != CUSTOM_MOUNT_BIND)
                        continue;

                r = is_device_node(cm->source);
                if (r == -ENOENT) {
                        /* The bind source might only appear as the image is put together, hence don't complain */
                        log_debug_errno(r, "Bind mount source %s not found, ignoring: %m", cm->source);
                        continue;
                }
                if (r < 0)
                        return log_error_errno(r, "Failed to stat %s: %m", cm->source);

                if (r) {
                        r = sd_bus_message_append(m, "(sv)", "DeviceAllow", "a(ss)", 1,
                                                  cm->source, cm->read_only ? "r" : "rw");
                        if (r < 0)
                                return log_error_errno(r, "Failed to append message arguments: %m");
                }
        }

        if (kill_signal != 0) {
                r = sd_bus_message_append(m, "(sv)", "KillSignal", "i", kill_signal);
                if (r < 0)
                        return bus_log_create_error(r);

                r = sd_bus_message_append(m, "(sv)", "KillMode", "s", "mixed");
                if (r < 0)
                        return bus_log_create_error(r);
        }

        return 0;
}