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
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int got_SIGHUP ; 
 int /*<<< orphan*/  handle_sighup ; 
 int /*<<< orphan*/  handle_sigterm ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_bgw_scheduler_register_signal_handlers(void)
{
	/*
	 * do not use the default `bgworker_die` sigterm handler because it does
	 * not respect critical sections
	 */
	pqsignal(SIGTERM, handle_sigterm);
	pqsignal(SIGHUP, handle_sighup);

	/* Some SIGHUPS may already have been dropped, so we must load the file here */
	got_SIGHUP = false;
	ProcessConfigFile(PGC_SIGHUP);
}