#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  worker ;
struct TYPE_4__ {int bgw_flags; int /*<<< orphan*/  bgw_function_name; int /*<<< orphan*/  bgw_library_name; scalar_t__ bgw_notify_pid; int /*<<< orphan*/  bgw_start_time; int /*<<< orphan*/  bgw_restart_time; int /*<<< orphan*/  bgw_name; } ;
typedef  TYPE_1__ BackgroundWorker ;

/* Variables and functions */
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_SHMEM_ACCESS ; 
 int /*<<< orphan*/  BGW_LAUNCHER_RESTART_TIME_S ; 
 int /*<<< orphan*/  BGW_MAXLEN ; 
 int /*<<< orphan*/  BgWorkerStart_RecoveryFinished ; 
 char* EXTENSION_NAME ; 
 int /*<<< orphan*/  RegisterBackgroundWorker (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

extern void
ts_bgw_cluster_launcher_register(void)
{
	BackgroundWorker worker;

	memset(&worker, 0, sizeof(worker));
	/* set up worker settings for our main worker */
	snprintf(worker.bgw_name, BGW_MAXLEN, "TimescaleDB Background Worker Launcher");
	worker.bgw_flags = BGWORKER_SHMEM_ACCESS | BGWORKER_BACKEND_DATABASE_CONNECTION;
	worker.bgw_restart_time = BGW_LAUNCHER_RESTART_TIME_S;

	/*
	 * Starting at BgWorkerStart_RecoveryFinished means we won't ever get
	 * started on a hot_standby see
	 * https://www.postgresql.org/docs/10/static/bgworker.html as it's not
	 * documented in bgworker.c.
	 */
	worker.bgw_start_time = BgWorkerStart_RecoveryFinished;
	worker.bgw_notify_pid = 0;
	snprintf(worker.bgw_library_name, BGW_MAXLEN, EXTENSION_NAME);
	snprintf(worker.bgw_function_name, BGW_MAXLEN, "ts_bgw_cluster_launcher_main");
	RegisterBackgroundWorker(&worker);
}