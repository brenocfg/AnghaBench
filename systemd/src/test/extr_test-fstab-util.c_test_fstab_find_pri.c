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
 int /*<<< orphan*/  assert_se (int) ; 
 int fstab_find_pri (char*,int*) ; 

__attribute__((used)) static void test_fstab_find_pri(void) {
        int pri = -1;

        assert_se(fstab_find_pri("pri", &pri) == 0);
        assert_se(pri == -1);

        assert_se(fstab_find_pri("pri=11", &pri) == 1);
        assert_se(pri == 11);

        assert_se(fstab_find_pri("opt,pri=12,opt", &pri) == 1);
        assert_se(pri == 12);

        assert_se(fstab_find_pri("opt,opt,pri=12,pri=13", &pri) == 1);
        assert_se(pri == 13);
}