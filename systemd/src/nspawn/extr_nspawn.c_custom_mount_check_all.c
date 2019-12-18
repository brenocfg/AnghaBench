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
struct TYPE_3__ {int /*<<< orphan*/  destination; } ;
typedef  TYPE_1__ CustomMount ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UID_INVALID ; 
 scalar_t__ USER_NAMESPACE_NO ; 
 TYPE_1__* arg_custom_mounts ; 
 size_t arg_n_custom_mounts ; 
 scalar_t__ arg_uid_shift ; 
 scalar_t__ arg_userns_chown ; 
 scalar_t__ arg_userns_mode ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ path_equal (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int custom_mount_check_all(void) {
        size_t i;

        for (i = 0; i < arg_n_custom_mounts; i++) {
                CustomMount *m = &arg_custom_mounts[i];

                if (path_equal(m->destination, "/") && arg_userns_mode != USER_NAMESPACE_NO) {
                        if (arg_userns_chown)
                                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                                       "--private-users-chown may not be combined with custom root mounts.");
                        else if (arg_uid_shift == UID_INVALID)
                                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                                       "--private-users with automatic UID shift may not be combined with custom root mounts.");
                }
        }

        return 0;
}