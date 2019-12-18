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
 int /*<<< orphan*/  INT_TO_PTR (char) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int trivial_compare_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_trivial_compare_func(void) {
        assert_se(trivial_compare_func(INT_TO_PTR('a'), INT_TO_PTR('a')) == 0);
        assert_se(trivial_compare_func(INT_TO_PTR('a'), INT_TO_PTR('b')) == -1);
        assert_se(trivial_compare_func(INT_TO_PTR('b'), INT_TO_PTR('a')) == 1);
}