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
typedef  int /*<<< orphan*/  sd_journal ;

/* Variables and functions */
 int /*<<< orphan*/  assert_ret (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int sd_journal_previous (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_check_number (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_check_numbers_up (sd_journal *j, int count) {
        for (int i = count; i >= 1; i--) {
                int r;
                test_check_number(j, i);
                assert_ret(r = sd_journal_previous(j));
                if (i == 1)
                        assert_se(r == 0);
                else
                        assert_se(r == 1);
        }

}