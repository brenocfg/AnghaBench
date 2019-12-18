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
typedef  int /*<<< orphan*/  TFun ;
typedef  int /*<<< orphan*/  TCase ;
typedef  int /*<<< orphan*/  Suite ;
typedef  int /*<<< orphan*/ * SFun ;

/* Variables and functions */
 int /*<<< orphan*/  suite_add_tcase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * suite_create (char const*) ; 
 int /*<<< orphan*/  tcase_add_checked_fixture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcase_add_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tcase_create (char*) ; 

__attribute__((used)) static Suite* create_suite(const char* name, TFun *tests, size_t num_tests, SFun setup, SFun teardown)
{
  size_t i;
  Suite *s = suite_create(name);

  for(i = 0; i < num_tests; i++) {
    /* Core test case */
    TCase *tc_core = tcase_create("Core");
    if ((setup != NULL) || (teardown != NULL)) {
      tcase_add_checked_fixture(tc_core, setup, teardown);
    }
    tcase_add_test(tc_core, tests[i]);
    suite_add_tcase(s, tc_core);
  }
  return s;
}