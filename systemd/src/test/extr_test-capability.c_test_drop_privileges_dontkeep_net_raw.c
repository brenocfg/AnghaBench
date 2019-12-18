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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ drop_privileges (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  show_capabilities () ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_flags ; 
 scalar_t__ test_gid ; 
 scalar_t__ test_uid ; 

__attribute__((used)) static void test_drop_privileges_dontkeep_net_raw(void) {
        int sock;

        sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
        assert_se(sock >= 0);
        safe_close(sock);

        assert_se(drop_privileges(test_uid, test_gid, test_flags) >= 0);
        assert_se(getuid() == test_uid);
        assert_se(getgid() == test_gid);
        show_capabilities();

        sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
        assert_se(sock < 0);
}