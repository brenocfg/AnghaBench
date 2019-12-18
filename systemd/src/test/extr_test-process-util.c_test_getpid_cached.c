#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ si_status; scalar_t__ si_code; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ CLD_EXITED ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 scalar_t__ getpid_cached () ; 
 scalar_t__ raw_getpid () ; 
 scalar_t__ wait_for_terminate (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static void test_getpid_cached(void) {
        siginfo_t si;
        pid_t a, b, c, d, e, f, child;

        a = raw_getpid();
        b = getpid_cached();
        c = getpid();

        assert_se(a == b && a == c);

        child = fork();
        assert_se(child >= 0);

        if (child == 0) {
                /* In child */
                a = raw_getpid();
                b = getpid_cached();
                c = getpid();

                assert_se(a == b && a == c);
                _exit(EXIT_SUCCESS);
        }

        d = raw_getpid();
        e = getpid_cached();
        f = getpid();

        assert_se(a == d && a == e && a == f);

        assert_se(wait_for_terminate(child, &si) >= 0);
        assert_se(si.si_status == 0);
        assert_se(si.si_code == CLD_EXITED);
}