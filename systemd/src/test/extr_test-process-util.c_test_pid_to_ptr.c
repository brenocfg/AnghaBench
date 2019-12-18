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
 int INT16_MAX ; 
 int INT16_MIN ; 
 int INT32_MAX ; 
 int INT32_MIN ; 
 int /*<<< orphan*/ * PID_TO_PTR (int) ; 
 int PTR_TO_PID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_se (int) ; 

__attribute__((used)) static void test_pid_to_ptr(void) {

        assert_se(PTR_TO_PID(NULL) == 0);
        assert_se(PID_TO_PTR(0) == NULL);

        assert_se(PTR_TO_PID(PID_TO_PTR(1)) == 1);
        assert_se(PTR_TO_PID(PID_TO_PTR(2)) == 2);
        assert_se(PTR_TO_PID(PID_TO_PTR(-1)) == -1);
        assert_se(PTR_TO_PID(PID_TO_PTR(-2)) == -2);

        assert_se(PTR_TO_PID(PID_TO_PTR(INT16_MAX)) == INT16_MAX);
        assert_se(PTR_TO_PID(PID_TO_PTR(INT16_MIN)) == INT16_MIN);

#if SIZEOF_PID_T >= 4
        assert_se(PTR_TO_PID(PID_TO_PTR(INT32_MAX)) == INT32_MAX);
        assert_se(PTR_TO_PID(PID_TO_PTR(INT32_MIN)) == INT32_MIN);
#endif
}