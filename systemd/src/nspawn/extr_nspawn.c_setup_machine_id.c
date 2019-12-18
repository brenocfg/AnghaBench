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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  ID128_PLAIN ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_uuid ; 
 int id128_read (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 char* prefix_roota (char const*,char*) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 
 int sd_id128_randomize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_machine_id(const char *directory) {
        const char *etc_machine_id;
        sd_id128_t id;
        int r;

        /* If the UUID in the container is already set, then that's what counts, and we use. If it isn't set, and the
         * caller passed --uuid=, then we'll pass it in the $container_uuid env var to PID 1 of the container. The
         * assumption is that PID 1 will then write it to /etc/machine-id to make it persistent. If --uuid= is not
         * passed we generate a random UUID, and pass it via $container_uuid. In effect this means that /etc/machine-id
         * in the container and our idea of the container UUID will always be in sync (at least if PID 1 in the
         * container behaves nicely). */

        etc_machine_id = prefix_roota(directory, "/etc/machine-id");

        r = id128_read(etc_machine_id, ID128_PLAIN, &id);
        if (r < 0) {
                if (!IN_SET(r, -ENOENT, -ENOMEDIUM)) /* If the file is missing or empty, we don't mind */
                        return log_error_errno(r, "Failed to read machine ID from container image: %m");

                if (sd_id128_is_null(arg_uuid)) {
                        r = sd_id128_randomize(&arg_uuid);
                        if (r < 0)
                                return log_error_errno(r, "Failed to acquire randomized machine UUID: %m");
                }
        } else {
                if (sd_id128_is_null(id))
                        return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "Machine ID in container image is zero, refusing.");

                arg_uuid = id;
        }

        return 0;
}