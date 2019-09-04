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
typedef  int /*<<< orphan*/  testsuite ;
struct subtest {int /*<<< orphan*/  name; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 struct subtest const USE_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_PSEH3_bug ; 
 int /*<<< orphan*/  test_PSEH3_bug2 ; 
 int /*<<< orphan*/  test_abnorm_1 ; 
 int /*<<< orphan*/  test_abnorm_2 ; 
 int /*<<< orphan*/  test_abnorm_3 ; 
 int /*<<< orphan*/  test_abnorm_4 ; 
 int /*<<< orphan*/  test_abnorm_5 ; 
 int /*<<< orphan*/  test_abnorm_6 ; 
 int /*<<< orphan*/  test_abnorm_7 ; 
 int /*<<< orphan*/  test_abnorm_8 ; 
 int /*<<< orphan*/  test_bug_4004 ; 
 int /*<<< orphan*/  test_bug_4663 ; 
 int /*<<< orphan*/  test_continue_execution_1 ; 
 int /*<<< orphan*/  test_continue_execution_10 ; 
 int /*<<< orphan*/  test_continue_execution_11 ; 
 int /*<<< orphan*/  test_continue_execution_12 ; 
 int /*<<< orphan*/  test_continue_execution_2 ; 
 int /*<<< orphan*/  test_continue_execution_3 ; 
 int /*<<< orphan*/  test_continue_execution_4 ; 
 int /*<<< orphan*/  test_continue_execution_5 ; 
 int /*<<< orphan*/  test_continue_execution_6 ; 
 int /*<<< orphan*/  test_continue_execution_7 ; 
 int /*<<< orphan*/  test_continue_execution_8 ; 
 int /*<<< orphan*/  test_continue_execution_9 ; 
 int /*<<< orphan*/  test_continue_search_1 ; 
 int /*<<< orphan*/  test_continue_search_2 ; 
 int /*<<< orphan*/  test_continue_search_3 ; 
 int /*<<< orphan*/  test_continue_search_4 ; 
 int /*<<< orphan*/  test_continue_search_5 ; 
 int /*<<< orphan*/  test_continue_search_6 ; 
 int /*<<< orphan*/  test_empty_1 ; 
 int /*<<< orphan*/  test_empty_2 ; 
 int /*<<< orphan*/  test_empty_3 ; 
 int /*<<< orphan*/  test_empty_4 ; 
 int /*<<< orphan*/  test_empty_5 ; 
 int /*<<< orphan*/  test_empty_6 ; 
 int /*<<< orphan*/  test_empty_7 ; 
 int /*<<< orphan*/  test_empty_8 ; 
 int /*<<< orphan*/  test_execute_handler_1 ; 
 int /*<<< orphan*/  test_execute_handler_10 ; 
 int /*<<< orphan*/  test_execute_handler_11 ; 
 int /*<<< orphan*/  test_execute_handler_12 ; 
 int /*<<< orphan*/  test_execute_handler_2 ; 
 int /*<<< orphan*/  test_execute_handler_3 ; 
 int /*<<< orphan*/  test_execute_handler_4 ; 
 int /*<<< orphan*/  test_execute_handler_5 ; 
 int /*<<< orphan*/  test_execute_handler_6 ; 
 int /*<<< orphan*/  test_execute_handler_7 ; 
 int /*<<< orphan*/  test_execute_handler_8 ; 
 int /*<<< orphan*/  test_execute_handler_9 ; 
 int /*<<< orphan*/  test_finally_1 ; 
 int /*<<< orphan*/  test_finally_10 ; 
 int /*<<< orphan*/  test_finally_11 ; 
 int /*<<< orphan*/  test_finally_12 ; 
 int /*<<< orphan*/  test_finally_13 ; 
 int /*<<< orphan*/  test_finally_14 ; 
 int /*<<< orphan*/  test_finally_2 ; 
 int /*<<< orphan*/  test_finally_3 ; 
 int /*<<< orphan*/  test_finally_4 ; 
 int /*<<< orphan*/  test_finally_5 ; 
 int /*<<< orphan*/  test_finally_6 ; 
 int /*<<< orphan*/  test_finally_7 ; 
 int /*<<< orphan*/  test_finally_8 ; 
 int /*<<< orphan*/  test_finally_9 ; 
 int /*<<< orphan*/  test_finally_goto ; 
 int /*<<< orphan*/  test_leave_1 ; 
 int /*<<< orphan*/  test_leave_2 ; 
 int /*<<< orphan*/  test_leave_3 ; 
 int /*<<< orphan*/  test_leave_4 ; 
 int /*<<< orphan*/  test_leave_5 ; 
 int /*<<< orphan*/  test_leave_6 ; 
 int /*<<< orphan*/  test_nested_exception ; 
 int /*<<< orphan*/  test_nested_locals_1 ; 
 int /*<<< orphan*/  test_nested_locals_2 ; 
 int /*<<< orphan*/  test_nested_locals_3 ; 
 int /*<<< orphan*/  test_unvolatile ; 
 int /*<<< orphan*/  test_unvolatile_2 ; 
 int /*<<< orphan*/  test_unvolatile_3 ; 
 int /*<<< orphan*/  test_unvolatile_4 ; 
 int /*<<< orphan*/  test_xcode_1 ; 
 int /*<<< orphan*/  test_xcode_2 ; 
 int /*<<< orphan*/  test_xcode_3 ; 
 int /*<<< orphan*/  test_xpointers_1 ; 
 int /*<<< orphan*/  test_xpointers_10 ; 
 int /*<<< orphan*/  test_xpointers_11 ; 
 int /*<<< orphan*/  test_xpointers_12 ; 
 int /*<<< orphan*/  test_xpointers_13 ; 
 int /*<<< orphan*/  test_xpointers_14 ; 
 int /*<<< orphan*/  test_xpointers_15 ; 
 int /*<<< orphan*/  test_xpointers_16 ; 
 int /*<<< orphan*/  test_xpointers_2 ; 
 int /*<<< orphan*/  test_xpointers_3 ; 
 int /*<<< orphan*/  test_xpointers_4 ; 
 int /*<<< orphan*/  test_xpointers_5 ; 
 int /*<<< orphan*/  test_xpointers_6 ; 
 int /*<<< orphan*/  test_xpointers_7 ; 
 int /*<<< orphan*/  test_xpointers_8 ; 
 int /*<<< orphan*/  test_xpointers_9 ; 
 int /*<<< orphan*/  test_yield_1 ; 
 int /*<<< orphan*/  test_yield_2 ; 
 int /*<<< orphan*/  test_yield_3 ; 
 int /*<<< orphan*/  test_yield_4 ; 
 int /*<<< orphan*/  test_yield_5 ; 
 int /*<<< orphan*/  test_yield_6 ; 

void testsuite_syntax(void)
{
	const struct subtest testsuite[] =
	{
		USE_TEST(test_empty_1),
		USE_TEST(test_empty_2),
		USE_TEST(test_empty_3),
		USE_TEST(test_empty_4),
		USE_TEST(test_empty_5),
		USE_TEST(test_empty_6),
		USE_TEST(test_empty_7),
		USE_TEST(test_empty_8),

		USE_TEST(test_execute_handler_1),
		USE_TEST(test_continue_execution_1),
		USE_TEST(test_continue_search_1),
		USE_TEST(test_execute_handler_2),
		USE_TEST(test_continue_execution_2),

		USE_TEST(test_execute_handler_3),
		USE_TEST(test_continue_execution_3),
		USE_TEST(test_continue_search_2),
		USE_TEST(test_execute_handler_4),
		USE_TEST(test_continue_execution_4),

		USE_TEST(test_execute_handler_5),
		USE_TEST(test_continue_execution_5),
		USE_TEST(test_continue_search_3),
		USE_TEST(test_execute_handler_6),
		USE_TEST(test_continue_execution_6),

		USE_TEST(test_execute_handler_7),
		USE_TEST(test_continue_execution_7),
		USE_TEST(test_continue_search_4),
		USE_TEST(test_execute_handler_8),
		USE_TEST(test_continue_execution_8),

		USE_TEST(test_execute_handler_9),
		USE_TEST(test_continue_execution_9),
		USE_TEST(test_continue_search_5),
		USE_TEST(test_execute_handler_10),
		USE_TEST(test_continue_execution_10),

		USE_TEST(test_execute_handler_11),
		USE_TEST(test_continue_execution_11),
		USE_TEST(test_continue_search_6),
		USE_TEST(test_execute_handler_12),
		USE_TEST(test_continue_execution_12),

		USE_TEST(test_leave_1),
		USE_TEST(test_leave_2),
		USE_TEST(test_leave_3),
		USE_TEST(test_leave_4),
		USE_TEST(test_leave_5),
		USE_TEST(test_leave_6),

		USE_TEST(test_yield_1),
		USE_TEST(test_yield_2),
		USE_TEST(test_yield_3),
		USE_TEST(test_yield_4),
		USE_TEST(test_yield_5),
		USE_TEST(test_yield_6),

		USE_TEST(test_finally_1),
		USE_TEST(test_finally_2),
		USE_TEST(test_finally_3),
		USE_TEST(test_finally_4),
		USE_TEST(test_finally_5),
		USE_TEST(test_finally_6),
		USE_TEST(test_finally_7),
		USE_TEST(test_finally_8),
		USE_TEST(test_finally_9),
		USE_TEST(test_finally_10),
		USE_TEST(test_finally_11),
		USE_TEST(test_finally_12),
		USE_TEST(test_finally_13),
		USE_TEST(test_finally_14),

		USE_TEST(test_xpointers_1),
		USE_TEST(test_xpointers_2),
		USE_TEST(test_xpointers_3),
		USE_TEST(test_xpointers_4),
		USE_TEST(test_xpointers_5),
		USE_TEST(test_xpointers_6),
		USE_TEST(test_xpointers_7),
		USE_TEST(test_xpointers_8),
		USE_TEST(test_xpointers_9),
		USE_TEST(test_xpointers_10),
		USE_TEST(test_xpointers_11),
		USE_TEST(test_xpointers_12),
		USE_TEST(test_xpointers_13),
		USE_TEST(test_xpointers_14),
		USE_TEST(test_xpointers_15),
		USE_TEST(test_xpointers_16),

		USE_TEST(test_xcode_1),
		USE_TEST(test_xcode_2),
		USE_TEST(test_xcode_3),

		USE_TEST(test_abnorm_1),
		USE_TEST(test_abnorm_2),
		USE_TEST(test_abnorm_3),
		USE_TEST(test_abnorm_4),
		USE_TEST(test_abnorm_5),
		USE_TEST(test_abnorm_6),
		USE_TEST(test_abnorm_7),
		USE_TEST(test_abnorm_8),

		USE_TEST(test_nested_locals_1),
		USE_TEST(test_nested_locals_2),
		USE_TEST(test_nested_locals_3),

		USE_TEST(test_bug_4004),
		USE_TEST(test_bug_4663),

		USE_TEST(test_unvolatile),
		USE_TEST(test_unvolatile_2),
#ifndef __cplusplus
		USE_TEST(test_unvolatile_3),
#endif
		USE_TEST(test_unvolatile_4),
		USE_TEST(test_finally_goto),
		USE_TEST(test_nested_exception),
		USE_TEST(test_PSEH3_bug),
		USE_TEST(test_PSEH3_bug2),
	};

	size_t i;

	for(i = 0; i < sizeof(testsuite) / sizeof(testsuite[0]); ++ i)
		ok(call_test(testsuite[i].func), "%s failed\n", testsuite[i].name);
}