#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* otArg; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * srcFile; } ;
typedef  TYPE_1__ fcResources ;
struct TYPE_5__ {scalar_t__ dstFile; } ;

/* Variables and functions */
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int freeCCtx (int /*<<< orphan*/ *) ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  waitUntilAllJobsCompleted (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int freeFileCompressionResources(fcResources* fcr)
{
    int ret = 0;
    waitUntilAllJobsCompleted(fcr->ctx);
    ret |= (fcr->srcFile != NULL) ? fclose(fcr->srcFile) : 0;
    ret |= (fcr->ctx != NULL) ? freeCCtx(fcr->ctx) : 0;
    if (fcr->otArg) {
        ret |= (fcr->otArg->dstFile != stdout) ? fclose(fcr->otArg->dstFile) : 0;
        free(fcr->otArg);
        /* no need to freeCCtx() on otArg->ctx because it should be the same context */
    }
    return ret;
}