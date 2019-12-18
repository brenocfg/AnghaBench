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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ parse_mode (char*,int*) ; 

__attribute__((used)) static void test_parse_mode(void) {
        mode_t m;

        assert_se(parse_mode("-1", &m) < 0);
        assert_se(parse_mode("", &m) < 0);
        assert_se(parse_mode("888", &m) < 0);
        assert_se(parse_mode("77777", &m) < 0);

        assert_se(parse_mode("544", &m) >= 0 && m == 0544);
        assert_se(parse_mode("777", &m) >= 0 && m == 0777);
        assert_se(parse_mode("7777", &m) >= 0 && m == 07777);
        assert_se(parse_mode("0", &m) >= 0 && m == 0);
}