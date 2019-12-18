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
struct TYPE_4__ {int /*<<< orphan*/  job_type; } ;
struct TYPE_5__ {TYPE_1__ fd; int /*<<< orphan*/  bgw_type; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FormData_bgw_job ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  get_job_type_from_name (int /*<<< orphan*/ *) ; 
 scalar_t__ ts_create_struct_from_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static BgwJob *
bgw_job_from_tuple(HeapTuple tuple, size_t alloc_size, MemoryContext mctx)
{
	BgwJob *job;

	/*
	 * allow for embedding with arbitrary alloc_size, which means we can't use
	 * the STRUCT_FROM_TUPLE macro
	 */
	Assert(alloc_size >= sizeof(BgwJob));
	job = (BgwJob *) ts_create_struct_from_tuple(tuple, mctx, alloc_size, sizeof(FormData_bgw_job));
	job->bgw_type = get_job_type_from_name(&job->fd.job_type);

	return job;
}