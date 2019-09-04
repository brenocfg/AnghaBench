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
typedef  int /*<<< orphan*/  paramValues_t ;
typedef  int /*<<< orphan*/  memoTable_t ;
typedef  int /*<<< orphan*/  contexts_t ;
typedef  int /*<<< orphan*/  constraint_t ;
struct TYPE_4__ {int /*<<< orphan*/  srcSize; int /*<<< orphan*/  maxBlockSize; } ;
typedef  TYPE_1__ buffers_t ;
typedef  int /*<<< orphan*/  BMK_benchResult_t ;

/* Variables and functions */
 int BETTER_RESULT ; 
 int /*<<< orphan*/  BMK_printWinnerOpt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUSTOM_LEVEL ; 
 scalar_t__ DEBUG ; 
 int /*<<< orphan*/  DISPLAY (char*,int) ; 
 scalar_t__ INFEASIBLE_THRESHOLD ; 
 int WORSE_RESULT ; 
 int allBench (int /*<<< orphan*/ *,TYPE_1__ const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int const) ; 
 scalar_t__ memoTableGet (int /*<<< orphan*/ * const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memoTableSet (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,int) ; 
 scalar_t__ redundantParams (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int benchMemo(BMK_benchResult_t* resultPtr,
                const buffers_t buf, const contexts_t ctx,
                const paramValues_t cParams,
                const constraint_t target,
                BMK_benchResult_t* winnerResult, memoTable_t* const memoTableArray,
                const int feas) {
    static int bmcount = 0;
    int res;

    if ( memoTableGet(memoTableArray, cParams) >= INFEASIBLE_THRESHOLD
      || redundantParams(cParams, target, buf.maxBlockSize) ) {
        return WORSE_RESULT;
    }

    res = allBench(resultPtr, buf, ctx, cParams, target, winnerResult, feas);

    if(DEBUG && !(bmcount % 250)) {
        DISPLAY("Count: %d\n", bmcount);
        bmcount++;
    }
    BMK_printWinnerOpt(stdout, CUSTOM_LEVEL, *resultPtr, cParams, target, buf.srcSize);

    if(res == BETTER_RESULT || feas) {
        memoTableSet(memoTableArray, cParams, 255); /* what happens if collisions are frequent */
    }
    return res;
}