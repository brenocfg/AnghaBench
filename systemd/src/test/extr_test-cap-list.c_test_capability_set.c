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
typedef  int uint64_t ;

/* Variables and functions */
 int CAP_AUDIT_CONTROL ; 
 int CAP_CHOWN ; 
 int CAP_DAC_OVERRIDE ; 
 int CAP_DAC_READ_SEARCH ; 
 int CAP_FOWNER ; 
 int CAP_MAC_OVERRIDE ; 
 int CAP_SETGID ; 
 int CAP_SETUID ; 
 int CAP_SYSLOG ; 
 int CAP_SYS_ADMIN ; 
 int CAP_SYS_PTRACE ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int capability_list_length () ; 
 scalar_t__ capability_set_from_string (char*,int*) ; 
 int /*<<< orphan*/  test_capability_set_one (int,char*) ; 

__attribute__((used)) static void test_capability_set(void) {
        uint64_t c;

        assert_se(capability_set_from_string(NULL, &c) == 0);
        assert_se(c == 0);

        assert_se(capability_set_from_string("", &c) == 0);
        assert_se(c == 0);

        assert_se(capability_set_from_string("0", &c) == 0);
        assert_se(c == UINT64_C(1));

        assert_se(capability_set_from_string("1", &c) == 0);
        assert_se(c == UINT64_C(1) << 1);

        assert_se(capability_set_from_string("0 1 2 3", &c) == 0);
        assert_se(c == (UINT64_C(1) << 4) - 1);

        test_capability_set_one(0, "");
        test_capability_set_one(
                UINT64_C(1) << CAP_DAC_OVERRIDE,
                "cap_dac_override");
        test_capability_set_one(
                UINT64_C(1) << CAP_DAC_OVERRIDE |
                UINT64_C(1) << capability_list_length(),
                "cap_dac_override");
        test_capability_set_one(
                UINT64_C(1) << capability_list_length(), "");
        test_capability_set_one(
                UINT64_C(1) << CAP_CHOWN |
                UINT64_C(1) << CAP_DAC_OVERRIDE |
                UINT64_C(1) << CAP_DAC_READ_SEARCH |
                UINT64_C(1) << CAP_FOWNER |
                UINT64_C(1) << CAP_SETGID |
                UINT64_C(1) << CAP_SETUID |
                UINT64_C(1) << CAP_SYS_PTRACE |
                UINT64_C(1) << CAP_SYS_ADMIN |
                UINT64_C(1) << CAP_AUDIT_CONTROL |
                UINT64_C(1) << CAP_MAC_OVERRIDE |
                UINT64_C(1) << CAP_SYSLOG |
                UINT64_C(1) << (capability_list_length() + 1),
                "cap_chown cap_dac_override cap_dac_read_search cap_fowner "
                "cap_setgid cap_setuid cap_sys_ptrace cap_sys_admin "
                "cap_audit_control cap_mac_override cap_syslog");
}