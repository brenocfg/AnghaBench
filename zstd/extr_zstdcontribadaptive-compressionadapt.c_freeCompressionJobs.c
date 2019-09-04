#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct TYPE_8__ {TYPE_2__ src; TYPE_1__ dst; } ;
typedef  TYPE_3__ jobDescription ;
struct TYPE_9__ {unsigned int numJobs; TYPE_3__* jobs; } ;
typedef  TYPE_4__ adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeCompressionJobs(adaptCCtx* ctx)
{
    unsigned u;
    for (u=0; u<ctx->numJobs; u++) {
        jobDescription job = ctx->jobs[u];
        free(job.dst.start);
        free(job.src.start);
    }
}