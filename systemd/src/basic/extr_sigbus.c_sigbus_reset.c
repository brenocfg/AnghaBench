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
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ n_installed ; 
 int /*<<< orphan*/  old_sigaction ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void sigbus_reset(void) {

        if (n_installed <= 0)
                return;

        n_installed--;

        if (n_installed == 0)
                assert_se(sigaction(SIGBUS, &old_sigaction, NULL) == 0);

        return;
}