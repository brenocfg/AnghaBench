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
struct TYPE_3__ {int /*<<< orphan*/  mctx; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/ * bgw_job_from_tuple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
bgw_job_tuple_found(TupleInfo *ti, void *const data)
{
	BgwJob **job_pp = data;

	*job_pp = bgw_job_from_tuple(ti->tuple, sizeof(BgwJob), ti->mctx);

	/*
	 * Return SCAN_CONTINUE because we check for multiple tuples as an error
	 * condition.
	 */
	return SCAN_CONTINUE;
}