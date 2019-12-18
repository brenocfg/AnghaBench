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
 int /*<<< orphan*/  LOG_ERR ; 
 int MS_BIND ; 
 int MS_RDONLY ; 
 int MS_REMOUNT ; 
 int MS_SLAVE ; 
 int /*<<< orphan*/  arg_machine ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  mkdir_p (char const*,int) ; 
 int mount_verbose (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* prefix_roota (char const*,char*) ; 
 char* strjoina (char*,int /*<<< orphan*/ ) ; 
 int userns_mkdir (char const*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_propagate(const char *root) {
        const char *p, *q;
        int r;

        (void) mkdir_p("/run/systemd/nspawn/", 0755);
        (void) mkdir_p("/run/systemd/nspawn/propagate", 0600);
        p = strjoina("/run/systemd/nspawn/propagate/", arg_machine);
        (void) mkdir_p(p, 0600);

        r = userns_mkdir(root, "/run/systemd", 0755, 0, 0);
        if (r < 0)
                return log_error_errno(r, "Failed to create /run/systemd: %m");

        r = userns_mkdir(root, "/run/systemd/nspawn", 0755, 0, 0);
        if (r < 0)
                return log_error_errno(r, "Failed to create /run/systemd/nspawn: %m");

        r = userns_mkdir(root, "/run/systemd/nspawn/incoming", 0600, 0, 0);
        if (r < 0)
                return log_error_errno(r, "Failed to create /run/systemd/nspawn/incoming: %m");

        q = prefix_roota(root, "/run/systemd/nspawn/incoming");
        r = mount_verbose(LOG_ERR, p, q, NULL, MS_BIND, NULL);
        if (r < 0)
                return r;

        r = mount_verbose(LOG_ERR, NULL, q, NULL, MS_BIND|MS_REMOUNT|MS_RDONLY, NULL);
        if (r < 0)
                return r;

        /* machined will MS_MOVE into that directory, and that's only
         * supported for non-shared mounts. */
        return mount_verbose(LOG_ERR, NULL, q, NULL, MS_SLAVE, NULL);
}