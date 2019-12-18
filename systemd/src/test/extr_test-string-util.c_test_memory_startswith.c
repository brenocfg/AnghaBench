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
 int /*<<< orphan*/  memory_startswith (char*,int,char*) ; 
 int streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_memory_startswith(void) {
        assert_se(streq(memory_startswith("", 0, ""), ""));
        assert_se(streq(memory_startswith("", 1, ""), ""));
        assert_se(streq(memory_startswith("x", 2, ""), "x"));
        assert_se(!memory_startswith("", 1, "x"));
        assert_se(!memory_startswith("", 1, "xxxxxxxx"));
        assert_se(streq(memory_startswith("xxx", 4, "x"), "xx"));
        assert_se(streq(memory_startswith("xxx", 4, "xx"), "x"));
        assert_se(streq(memory_startswith("xxx", 4, "xxx"), ""));
        assert_se(!memory_startswith("xxx", 4, "xxxx"));
}