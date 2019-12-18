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
 scalar_t__ ascii_strcasecmp_n (char*,char*,int) ; 
 int /*<<< orphan*/  assert_se (int) ; 

__attribute__((used)) static void test_ascii_strcasecmp_n(void) {

        assert_se(ascii_strcasecmp_n("", "", 0) == 0);
        assert_se(ascii_strcasecmp_n("", "", 1) == 0);
        assert_se(ascii_strcasecmp_n("", "a", 1) < 0);
        assert_se(ascii_strcasecmp_n("", "a", 2) < 0);
        assert_se(ascii_strcasecmp_n("a", "", 1) > 0);
        assert_se(ascii_strcasecmp_n("a", "", 2) > 0);
        assert_se(ascii_strcasecmp_n("a", "a", 1) == 0);
        assert_se(ascii_strcasecmp_n("a", "a", 2) == 0);
        assert_se(ascii_strcasecmp_n("a", "b", 1) < 0);
        assert_se(ascii_strcasecmp_n("a", "b", 2) < 0);
        assert_se(ascii_strcasecmp_n("b", "a", 1) > 0);
        assert_se(ascii_strcasecmp_n("b", "a", 2) > 0);
        assert_se(ascii_strcasecmp_n("xxxxyxxxx", "xxxxYxxxx", 9) == 0);
        assert_se(ascii_strcasecmp_n("xxxxxxxxx", "xxxxyxxxx", 9) < 0);
        assert_se(ascii_strcasecmp_n("xxxxXxxxx", "xxxxyxxxx", 9) < 0);
        assert_se(ascii_strcasecmp_n("xxxxxxxxx", "xxxxYxxxx", 9) < 0);
        assert_se(ascii_strcasecmp_n("xxxxXxxxx", "xxxxYxxxx", 9) < 0);

        assert_se(ascii_strcasecmp_n("xxxxYxxxx", "xxxxYxxxx", 9) == 0);
        assert_se(ascii_strcasecmp_n("xxxxyxxxx", "xxxxxxxxx", 9) > 0);
        assert_se(ascii_strcasecmp_n("xxxxyxxxx", "xxxxXxxxx", 9) > 0);
        assert_se(ascii_strcasecmp_n("xxxxYxxxx", "xxxxxxxxx", 9) > 0);
        assert_se(ascii_strcasecmp_n("xxxxYxxxx", "xxxxXxxxx", 9) > 0);
}