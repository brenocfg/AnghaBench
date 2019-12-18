#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double nanoSecPerRun; } ;
struct TYPE_6__ {int runBudget_ns; double nbLoops; unsigned long long timeSpent_ns; TYPE_2__ fastestRun; } ;
typedef  int PTime ;
typedef  TYPE_1__ BMK_timedFnState_t ;
typedef  TYPE_2__ BMK_runTime_t ;
typedef  int /*<<< orphan*/  const BMK_runOutcome_t ;
typedef  int /*<<< orphan*/  BMK_benchParams_t ;

/* Variables and functions */
 int /*<<< orphan*/  const BMK_benchFunction (int /*<<< orphan*/ ,double) ; 
 TYPE_2__ BMK_extract_runTime (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BMK_isSuccessful_runOutcome (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const BMK_setValid_runTime (TYPE_2__) ; 
 double MIN (double,double) ; 
 int /*<<< orphan*/  assert (int) ; 

BMK_runOutcome_t BMK_benchTimedFn(BMK_timedFnState_t* cont,
                                  BMK_benchParams_t p)
{
    PTime const runBudget_ns = cont->runBudget_ns;
    PTime const runTimeMin_ns = runBudget_ns / 2;
    int completed = 0;
    BMK_runTime_t bestRunTime = cont->fastestRun;

    while (!completed) {
        BMK_runOutcome_t const runResult = BMK_benchFunction(p, cont->nbLoops);

        if(!BMK_isSuccessful_runOutcome(runResult)) { /* error : move out */
            return runResult;
        }

        {   BMK_runTime_t const newRunTime = BMK_extract_runTime(runResult);
            double const loopDuration_ns = newRunTime.nanoSecPerRun * cont->nbLoops;

            cont->timeSpent_ns += (unsigned long long)loopDuration_ns;

            /* estimate nbLoops for next run to last approximately 1 second */
            if (loopDuration_ns > (runBudget_ns / 50)) {
                double const fastestRun_ns = MIN(bestRunTime.nanoSecPerRun, newRunTime.nanoSecPerRun);
                cont->nbLoops = (unsigned)(runBudget_ns / fastestRun_ns) + 1;
            } else {
                /* previous run was too short : blindly increase workload by x multiplier */
                const unsigned multiplier = 10;
                assert(cont->nbLoops < ((unsigned)-1) / multiplier);  /* avoid overflow */
                cont->nbLoops *= multiplier;
            }

            if(loopDuration_ns < runTimeMin_ns) {
                /* don't report results for which benchmark run time was too small : increased risks of rounding errors */
                assert(completed == 0);
                continue;
            } else {
                if(newRunTime.nanoSecPerRun < bestRunTime.nanoSecPerRun) {
                    bestRunTime = newRunTime;
                }
                completed = 1;
            }
        }
    }   /* while (!completed) */

    return BMK_setValid_runTime(bestRunTime);
}