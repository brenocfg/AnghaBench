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
 int fstab_test_yes_no_option (char*,char*) ; 

__attribute__((used)) static void test_fstab_yes_no_option(void) {
        assert_se(fstab_test_yes_no_option("nofail,fail,nofail", "nofail\0fail\0") == true);
        assert_se(fstab_test_yes_no_option("nofail,nofail,fail", "nofail\0fail\0") == false);
        assert_se(fstab_test_yes_no_option("abc,cde,afail", "nofail\0fail\0") == false);
        assert_se(fstab_test_yes_no_option("nofail,fail=0,nofail=0", "nofail\0fail\0") == true);
        assert_se(fstab_test_yes_no_option("nofail,nofail=0,fail=0", "nofail\0fail\0") == false);
}