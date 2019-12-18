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
 scalar_t__ CAP_LAST_CAP ; 
 int /*<<< orphan*/  PR_CAPBSET_READ ; 
 int /*<<< orphan*/  assert_se (int) ; 
 unsigned long cap_last_cap () ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void test_last_cap_probe(void) {
        unsigned long p = (unsigned long)CAP_LAST_CAP;

        if (prctl(PR_CAPBSET_READ, p) < 0) {
                for (p--; p > 0; p --)
                        if (prctl(PR_CAPBSET_READ, p) >= 0)
                                break;
        } else {
                for (;; p++)
                        if (prctl(PR_CAPBSET_READ, p+1) < 0)
                                break;
        }

        assert_se(p != 0);
        assert_se(p == cap_last_cap());
}