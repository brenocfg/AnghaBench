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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SIGNALS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int sigismember (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_block_signals(void) {
        sigset_t ss;

        assert_se(sigprocmask(0, NULL, &ss) >= 0);

        assert_se(sigismember(&ss, SIGUSR1) == 0);
        assert_se(sigismember(&ss, SIGALRM) == 0);
        assert_se(sigismember(&ss, SIGVTALRM) == 0);

        {
                BLOCK_SIGNALS(SIGUSR1, SIGVTALRM);

                assert_se(sigprocmask(0, NULL, &ss) >= 0);
                assert_se(sigismember(&ss, SIGUSR1) == 1);
                assert_se(sigismember(&ss, SIGALRM) == 0);
                assert_se(sigismember(&ss, SIGVTALRM) == 1);

        }

        assert_se(sigprocmask(0, NULL, &ss) >= 0);
        assert_se(sigismember(&ss, SIGUSR1) == 0);
        assert_se(sigismember(&ss, SIGALRM) == 0);
        assert_se(sigismember(&ss, SIGVTALRM) == 0);
}