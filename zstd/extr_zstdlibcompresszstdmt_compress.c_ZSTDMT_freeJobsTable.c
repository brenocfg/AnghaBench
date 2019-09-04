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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_4__ {int /*<<< orphan*/  job_cond; int /*<<< orphan*/  job_mutex; } ;
typedef  TYPE_1__ ZSTDMT_jobDescription ;
typedef  size_t U32 ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_freeJobsTable(ZSTDMT_jobDescription* jobTable, U32 nbJobs, ZSTD_customMem cMem)
{
    U32 jobNb;
    if (jobTable == NULL) return;
    for (jobNb=0; jobNb<nbJobs; jobNb++) {
        ZSTD_pthread_mutex_destroy(&jobTable[jobNb].job_mutex);
        ZSTD_pthread_cond_destroy(&jobTable[jobNb].job_cond);
    }
    ZSTD_free(jobTable, cMem);
}