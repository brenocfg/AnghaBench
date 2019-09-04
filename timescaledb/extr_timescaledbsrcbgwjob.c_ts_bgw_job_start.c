#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  application_name; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ BgwJob ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int4out ; 
 int /*<<< orphan*/  job_entrypoint_function_name ; 
 int /*<<< orphan*/ * ts_bgw_start_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

BackgroundWorkerHandle *
ts_bgw_job_start(BgwJob *job)
{
	char *job_id_text;

	job_id_text = DatumGetCString(DirectFunctionCall1(int4out, Int32GetDatum(job->fd.id)));

	return ts_bgw_start_worker(job_entrypoint_function_name,
							   NameStr(job->fd.application_name),
							   job_id_text);
}