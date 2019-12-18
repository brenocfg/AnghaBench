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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 scalar_t__ lchown (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkdir_errno_wrapper (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mkdir_userns(const char *path, mode_t mode, uid_t uid_shift) {
        int r;

        assert(path);

        r = mkdir_errno_wrapper(path, mode);
        if (r < 0 && r != -EEXIST)
                return r;

        if (uid_shift == UID_INVALID)
                return 0;

        if (lchown(path, uid_shift, uid_shift) < 0)
                return -errno;

        return 0;
}