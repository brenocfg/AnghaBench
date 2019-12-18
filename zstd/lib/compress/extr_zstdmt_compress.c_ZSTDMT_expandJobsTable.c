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
struct TYPE_3__ {int jobIDMask; int /*<<< orphan*/ * jobs; int /*<<< orphan*/  cMem; } ;
typedef  TYPE_1__ ZSTDMT_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTDMT_createJobsTable (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_freeJobsTable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memory_allocation ; 

__attribute__((used)) static size_t ZSTDMT_expandJobsTable (ZSTDMT_CCtx* mtctx, U32 nbWorkers) {
    U32 nbJobs = nbWorkers + 2;
    if (nbJobs > mtctx->jobIDMask+1) {  /* need more job capacity */
        ZSTDMT_freeJobsTable(mtctx->jobs, mtctx->jobIDMask+1, mtctx->cMem);
        mtctx->jobIDMask = 0;
        mtctx->jobs = ZSTDMT_createJobsTable(&nbJobs, mtctx->cMem);
        if (mtctx->jobs==NULL) return ERROR(memory_allocation);
        assert((nbJobs != 0) && ((nbJobs & (nbJobs - 1)) == 0));  /* ensure nbJobs is a power of 2 */
        mtctx->jobIDMask = nbJobs - 1;
    }
    return 0;
}