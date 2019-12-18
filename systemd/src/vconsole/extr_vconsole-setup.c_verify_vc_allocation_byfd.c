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
struct vt_stat {int /*<<< orphan*/  v_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT_GETSTATE ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct vt_stat*) ; 
 int verify_vc_allocation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_vc_allocation_byfd(int fd) {
        struct vt_stat vcs = {};

        if (ioctl(fd, VT_GETSTATE, &vcs) < 0)
                return -errno;

        return verify_vc_allocation(vcs.v_active);
}