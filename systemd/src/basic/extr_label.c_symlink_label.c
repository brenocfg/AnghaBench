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
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  mac_selinux_create_file_clear () ; 
 int mac_selinux_create_file_prepare (char const*,int /*<<< orphan*/ ) ; 
 int mac_smack_fix (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ symlink (char const*,char const*) ; 

int symlink_label(const char *old_path, const char *new_path) {
        int r;

        assert(old_path);
        assert(new_path);

        r = mac_selinux_create_file_prepare(new_path, S_IFLNK);
        if (r < 0)
                return r;

        if (symlink(old_path, new_path) < 0)
                r = -errno;

        mac_selinux_create_file_clear();

        if (r < 0)
                return r;

        return mac_smack_fix(new_path, 0);
}