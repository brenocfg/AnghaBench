#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  params; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ winnerInfo_t ;
struct TYPE_17__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_2__ paramValues_t ;
typedef  int /*<<< orphan*/  memoTable_t ;
typedef  int /*<<< orphan*/  contexts_t ;
typedef  int /*<<< orphan*/  constraint_t ;
struct TYPE_18__ {int /*<<< orphan*/  srcSize; int /*<<< orphan*/  maxBlockSize; } ;
typedef  TYPE_3__ buffers_t ;
typedef  int /*<<< orphan*/  ZSTD_strategy ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_printWinnerOpt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKTIME (TYPE_1__) ; 
 int /*<<< orphan*/  CUSTOM_LEVEL ; 
 int /*<<< orphan*/  DEBUGOUTPUT (char*) ; 
 TYPE_2__ cParamUnsetMin (TYPE_2__) ; 
 TYPE_1__ climbOnce (int /*<<< orphan*/  const,int /*<<< orphan*/ *,TYPE_3__ const,int /*<<< orphan*/  const,TYPE_2__) ; 
 scalar_t__ compareResultLT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emptyParams () ; 
 TYPE_1__ initWinnerInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randomConstrainedParams (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 scalar_t__ redundantParams (TYPE_2__,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 size_t strt_ind ; 

__attribute__((used)) static winnerInfo_t
optimizeFixedStrategy(const buffers_t buf, const contexts_t ctx,
                      const constraint_t target, paramValues_t paramTarget,
                      const ZSTD_strategy strat,
                      memoTable_t* memoTableArray, const int tries)
{
    int i = 0;

    paramValues_t init;
    winnerInfo_t winnerInfo, candidateInfo;
    winnerInfo = initWinnerInfo(emptyParams());
    /* so climb is given the right fixed strategy */
    paramTarget.vals[strt_ind] = strat;
    /* to pass ZSTD_checkCParams */
    paramTarget = cParamUnsetMin(paramTarget);

    init = paramTarget;

    for(i = 0; i < tries; i++) {
        DEBUGOUTPUT("Restart\n");
        do {
            randomConstrainedParams(&init, memoTableArray, strat);
        } while(redundantParams(init, target, buf.maxBlockSize));
        candidateInfo = climbOnce(target, memoTableArray, buf, ctx, init);
        if (compareResultLT(winnerInfo.result, candidateInfo.result, target, buf.srcSize)) {
            winnerInfo = candidateInfo;
            BMK_printWinnerOpt(stdout, CUSTOM_LEVEL, winnerInfo.result, winnerInfo.params, target, buf.srcSize);
            i = 0;
            continue;
        }
        CHECKTIME(winnerInfo);
        i++;
    }
    return winnerInfo;
}