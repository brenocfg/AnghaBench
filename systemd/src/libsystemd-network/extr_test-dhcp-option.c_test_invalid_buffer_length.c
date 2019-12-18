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
typedef  int /*<<< orphan*/  DHCPMessage ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  dhcp_option_parse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_invalid_buffer_length(void) {
        DHCPMessage message;

        assert_se(dhcp_option_parse(&message, 0, NULL, NULL, NULL) == -EINVAL);
        assert_se(dhcp_option_parse(&message, sizeof(DHCPMessage) - 1, NULL, NULL, NULL) == -EINVAL);
}