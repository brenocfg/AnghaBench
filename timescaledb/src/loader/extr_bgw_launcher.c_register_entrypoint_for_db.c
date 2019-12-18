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
typedef  int /*<<< orphan*/  VirtualTransactionId ;
struct TYPE_4__ {int bgw_flags; int /*<<< orphan*/  bgw_extra; int /*<<< orphan*/  bgw_main_arg; int /*<<< orphan*/  bgw_notify_pid; int /*<<< orphan*/  bgw_function_name; int /*<<< orphan*/  bgw_library_name; int /*<<< orphan*/  bgw_start_time; int /*<<< orphan*/  bgw_restart_time; int /*<<< orphan*/  bgw_name; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;
typedef  TYPE_1__ BackgroundWorker ;

/* Variables and functions */
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_SHMEM_ACCESS ; 
 char* BGW_ENTRYPOINT_FUNCNAME ; 
 int /*<<< orphan*/  BGW_MAXLEN ; 
 int /*<<< orphan*/  BGW_NEVER_RESTART ; 
 int /*<<< orphan*/  BgWorkerStart_RecoveryFinished ; 
 char* EXTENSION_NAME ; 
 int /*<<< orphan*/  MyProcPid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int RegisterDynamicBackgroundWorker (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
register_entrypoint_for_db(Oid db_id, VirtualTransactionId vxid, BackgroundWorkerHandle **handle)
{
	BackgroundWorker worker;

	memset(&worker, 0, sizeof(worker));
	snprintf(worker.bgw_name, BGW_MAXLEN, "TimescaleDB Background Worker Scheduler");
	worker.bgw_flags = BGWORKER_SHMEM_ACCESS | BGWORKER_BACKEND_DATABASE_CONNECTION;
	worker.bgw_restart_time = BGW_NEVER_RESTART;
	worker.bgw_start_time = BgWorkerStart_RecoveryFinished;
	snprintf(worker.bgw_library_name, BGW_MAXLEN, EXTENSION_NAME);
	snprintf(worker.bgw_function_name, BGW_MAXLEN, BGW_ENTRYPOINT_FUNCNAME);
	worker.bgw_notify_pid = MyProcPid;
	worker.bgw_main_arg = ObjectIdGetDatum(db_id);
	memcpy(worker.bgw_extra, &vxid, sizeof(VirtualTransactionId));

	return RegisterDynamicBackgroundWorker(&worker, handle);
}