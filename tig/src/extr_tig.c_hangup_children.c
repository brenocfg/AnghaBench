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
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  killpg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
hangup_children(void)
{
	if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
		return;
	killpg(getpid(), SIGHUP);
}