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
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_equal (char**,char**) ; 
 char** strv_skip (char**,size_t) ; 

__attribute__((used)) static void test_strv_skip_one(char **a, size_t n, char **b) {
        a = strv_skip(a, n);
        assert_se(strv_equal(a, b));
}