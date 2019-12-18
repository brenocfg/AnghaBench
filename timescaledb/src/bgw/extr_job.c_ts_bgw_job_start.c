#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_9__ {int /*<<< orphan*/  application_name; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_1__ fd; } ;
struct TYPE_10__ {struct TYPE_10__* data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ BgwJob ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_entrypoint_function_name ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 int /*<<< orphan*/ * ts_bgw_start_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

BackgroundWorkerHandle *
ts_bgw_job_start(BgwJob *job, Oid user_uid)
{
	int32 job_id = Int32GetDatum(job->fd.id);
	StringInfo si = makeStringInfo();
	BackgroundWorkerHandle *bgw_handle;

	/* Changing this requires changes to ts_bgw_job_entrypoint */
	appendStringInfo(si, "%u %d", user_uid, job_id);

	bgw_handle = ts_bgw_start_worker(job_entrypoint_function_name,
									 NameStr(job->fd.application_name),
									 si->data);

	pfree(si->data);
	pfree(si);
	return bgw_handle;
}