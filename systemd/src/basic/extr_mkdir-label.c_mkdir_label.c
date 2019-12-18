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
 int mac_selinux_create_file_prepare (char const*,int /*<<< orphan*/ ) ; 
 int mac_smack_fix (char const*,int /*<<< orphan*/ ) ; 
 int mkdir_errno_wrapper (char const*,int /*<<< orphan*/ ) ; 

int mkdir_label(const char *path, mode_t mode) {
        int r;

        assert(path);

        r = mac_selinux_create_file_prepare(path, S_IFDIR);
        if (r < 0)
                return r;

        r = mkdir_errno_wrapper(path, mode);
        mac_selinux_create_file_clear();
        if (r < 0)
                return r;

        return mac_smack_fix(path, 0);
}