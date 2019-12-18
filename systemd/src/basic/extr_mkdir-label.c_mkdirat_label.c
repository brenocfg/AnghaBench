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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  mac_selinux_create_file_clear () ; 
 int mac_selinux_create_file_prepare_at (int,char const*,int /*<<< orphan*/ ) ; 
 int mac_smack_fix_at (int,char const*,int /*<<< orphan*/ ) ; 
 int mkdirat_errno_wrapper (int,char const*,int /*<<< orphan*/ ) ; 

int mkdirat_label(int dirfd, const char *path, mode_t mode) {
        int r;

        assert(path);

        r = mac_selinux_create_file_prepare_at(dirfd, path, S_IFDIR);
        if (r < 0)
                return r;

        r = mkdirat_errno_wrapper(dirfd, path, mode);
        mac_selinux_create_file_clear();
        if (r < 0)
                return r;

        return mac_smack_fix_at(dirfd, path, 0);
}