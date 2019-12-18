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
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_SECURITY ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  condition_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ condition_test (int /*<<< orphan*/ *) ; 
 scalar_t__ is_efi_secure_boot () ; 
 scalar_t__ mac_apparmor_use () ; 
 scalar_t__ mac_selinux_use () ; 
 scalar_t__ mac_smack_use () ; 
 scalar_t__ mac_tomoyo_use () ; 
 scalar_t__ use_audit () ; 
 scalar_t__ use_ima () ; 

__attribute__((used)) static void test_condition_test_security(void) {
        Condition *condition;

        condition = condition_new(CONDITION_SECURITY, "garbage oifdsjfoidsjoj", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "selinux", false, true);
        assert_se(condition);
        assert_se(condition_test(condition) != mac_selinux_use());
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "apparmor", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == mac_apparmor_use());
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "tomoyo", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == mac_tomoyo_use());
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "ima", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == use_ima());
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "smack", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == mac_smack_use());
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "audit", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == use_audit());
        condition_free(condition);

        condition = condition_new(CONDITION_SECURITY, "uefi-secureboot", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == is_efi_secure_boot());
        condition_free(condition);
}