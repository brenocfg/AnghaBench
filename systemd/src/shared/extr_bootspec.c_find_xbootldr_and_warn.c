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
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOKEY ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  path_is_absolute (char const*) ; 
 int /*<<< orphan*/  path_is_valid (char const*) ; 
 char* strdup (char const*) ; 
 int verify_xbootldr (char const*,int,int,int /*<<< orphan*/ *) ; 

int find_xbootldr_and_warn(
                const char *path,
                bool unprivileged_mode,
                char **ret_path,
                sd_id128_t *ret_uuid) {

        int r;

        /* Similar to find_esp_and_warn(), but finds the XBOOTLDR partition. Returns the same errors. */

        if (path) {
                r = verify_xbootldr(path, false, unprivileged_mode, ret_uuid);
                if (r < 0)
                        return r;

                goto found;
        }

        path = getenv("SYSTEMD_XBOOTLDR_PATH");
        if (path) {
                if (!path_is_valid(path) || !path_is_absolute(path))
                        return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "$SYSTEMD_XBOOTLDR_PATH does not refer to absolute path, refusing to use it: %s",
                                               path);

                goto found;
        }

        r = verify_xbootldr("/boot", true, unprivileged_mode, ret_uuid);
        if (r >= 0) {
                path = "/boot";
                goto found;
        }
        if (!IN_SET(r, -ENOENT, -EADDRNOTAVAIL)) /* This one is not it */
                return r;

        return -ENOKEY;

found:
        if (ret_path) {
                char *c;

                c = strdup(path);
                if (!c)
                        return log_oom();

                *ret_path = c;
        }

        return 0;
}