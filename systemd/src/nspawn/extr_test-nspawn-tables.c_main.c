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
 int /*<<< orphan*/  RESOLV_CONF_MODE ; 
 int /*<<< orphan*/  TIMEZONE_MODE ; 
 int /*<<< orphan*/  resolv_conf_mode ; 
 int /*<<< orphan*/  test_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timezone_mode ; 

int main(int argc, char **argv) {
        test_table(resolv_conf_mode, RESOLV_CONF_MODE);
        test_table(timezone_mode, TIMEZONE_MODE);

        return 0;
}