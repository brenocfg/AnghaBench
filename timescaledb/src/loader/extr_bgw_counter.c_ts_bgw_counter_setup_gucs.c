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
 int /*<<< orphan*/  DefineCustomIntVariable (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGC_POSTMASTER ; 
 int /*<<< orphan*/  ts_guc_max_background_workers ; 

extern void
ts_bgw_counter_setup_gucs(void)
{
	DefineCustomIntVariable("timescaledb.max_background_workers",
							"Maximum background worker processes allocated to TimescaleDB",
							"Max background worker processes allocated to TimescaleDB - set to at "
							"least 1 + number of databases in Postgres instance to use background "
							"workers ",
							&ts_guc_max_background_workers,
							ts_guc_max_background_workers,
							0,
							1000, /* no reasonable way to have more than
								   * 1000 background workers */
							PGC_POSTMASTER,
							0,
							NULL,
							NULL,
							NULL);
}