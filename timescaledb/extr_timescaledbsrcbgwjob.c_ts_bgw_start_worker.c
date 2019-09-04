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
struct TYPE_3__ {int bgw_flags; int /*<<< orphan*/  bgw_extra; int /*<<< orphan*/  bgw_function_name; int /*<<< orphan*/  bgw_library_name; int /*<<< orphan*/  bgw_name; int /*<<< orphan*/  bgw_main_arg; int /*<<< orphan*/  bgw_notify_pid; int /*<<< orphan*/  bgw_restart_time; int /*<<< orphan*/  bgw_start_time; } ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;
typedef  TYPE_1__ BackgroundWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_SHMEM_ACCESS ; 
 scalar_t__ BGW_EXTRALEN ; 
 scalar_t__ BGW_MAXLEN ; 
 int /*<<< orphan*/  BGW_NEVER_RESTART ; 
 int /*<<< orphan*/  BgWorkerStart_RecoveryFinished ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  MyProcPid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterDynamicBackgroundWorker (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 char const* ts_extension_get_so_name () ; 

BackgroundWorkerHandle *
ts_bgw_start_worker(const char *function, const char *name, const char *extra)
{
	BackgroundWorker worker = {
		.bgw_flags = BGWORKER_SHMEM_ACCESS | BGWORKER_BACKEND_DATABASE_CONNECTION,
		.bgw_start_time = BgWorkerStart_RecoveryFinished,
		.bgw_restart_time = BGW_NEVER_RESTART,
		.bgw_notify_pid = MyProcPid,
		.bgw_main_arg = ObjectIdGetDatum(MyDatabaseId),
	};
	BackgroundWorkerHandle *handle = NULL;

	StrNCpy(worker.bgw_name, name, BGW_MAXLEN);
	StrNCpy(worker.bgw_library_name, ts_extension_get_so_name(), BGW_MAXLEN);
	StrNCpy(worker.bgw_function_name, function, BGW_MAXLEN);

	Assert(strlen(extra) < BGW_EXTRALEN);
	StrNCpy(worker.bgw_extra, extra, BGW_EXTRALEN);

	if (!RegisterDynamicBackgroundWorker(&worker, &handle))
		return NULL;
	return handle;
}