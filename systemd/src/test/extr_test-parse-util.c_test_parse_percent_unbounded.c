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
 int parse_percent_unbounded (char*) ; 

__attribute__((used)) static void test_parse_percent_unbounded(void) {
        assert_se(parse_percent_unbounded("101%") == 101);
        assert_se(parse_percent_unbounded("400%") == 400);
}