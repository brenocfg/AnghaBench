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
struct statfs {int /*<<< orphan*/  f_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SUPER_MAGIC ; 
 int ENOENT ; 
 int F_TYPE_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ statfs (char*,struct statfs*) ; 

__attribute__((used)) static int check_btrfs(void) {
        struct statfs sfs;

        if (statfs("/var/lib/machines", &sfs) < 0) {
                if (errno != ENOENT)
                        return -errno;

                if (statfs("/var/lib", &sfs) < 0)
                        return -errno;
        }

        return F_TYPE_EQUAL(sfs.f_type, BTRFS_SUPER_MAGIC);
}