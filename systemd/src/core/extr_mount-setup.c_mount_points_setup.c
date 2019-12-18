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
 int mount_one (scalar_t__,int) ; 
 scalar_t__ mount_table ; 

__attribute__((used)) static int mount_points_setup(unsigned n, bool loaded_policy) {
        unsigned i;
        int r = 0;

        for (i = 0; i < n; i ++) {
                int j;

                j = mount_one(mount_table + i, loaded_policy);
                if (j != 0 && r >= 0)
                        r = j;
        }

        return r;
}