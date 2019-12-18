#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winners ;
typedef  int /*<<< orphan*/  winnerInfo_t ;
typedef  void* paramValues_t ;
struct TYPE_13__ {int /*<<< orphan*/  dictSize; } ;
typedef  TYPE_1__ contexts_t ;
struct TYPE_14__ {int /*<<< orphan*/  srcSize; int /*<<< orphan*/  maxBlockSize; } ;
typedef  TYPE_2__ buffers_t ;
typedef  int /*<<< orphan*/  UTIL_time_t ;
struct TYPE_15__ {int cSpeed; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ BMK_benchResult_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_benchParam (TYPE_3__*,TYPE_2__ const,TYPE_1__ const,void* const) ; 
 int /*<<< orphan*/  BMK_init_level_constraints (int) ; 
 int /*<<< orphan*/  BMK_saveAndPrint_cLevelTable (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMK_seed (int /*<<< orphan*/ *,void*,TYPE_2__ const,TYPE_1__ const) ; 
 int /*<<< orphan*/  BMK_selectRandomStart (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,TYPE_2__ const,TYPE_1__ const) ; 
 scalar_t__ BMK_timeSpan_s (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int MB_UNIT ; 
 int /*<<< orphan*/  NB_LEVELS_TRACKED ; 
 int /*<<< orphan*/  UTIL_getTime () ; 
 int /*<<< orphan*/  ZSTD_getCParams (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ZSTD_maxCLevel () ; 
 int /*<<< orphan*/  assert (int) ; 
 void* cParamsToPVals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 scalar_t__ g_noSeed ; 
 scalar_t__ g_singleRun ; 
 int g_target ; 
 scalar_t__ g_timeLimit_s ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void BMK_generate_cLevelTable(const buffers_t buf, const contexts_t ctx)
{
    paramValues_t params;
    winnerInfo_t winners[NB_LEVELS_TRACKED+1];
    const char* const rfName = "grillResults.txt";
    FILE* const f = fopen(rfName, "w");

    /* init */
    assert(g_singleRun==0);
    memset(winners, 0, sizeof(winners));
    if (f==NULL) { DISPLAY("error opening %s \n", rfName); exit(1); }

    if (g_target) {
        BMK_init_level_constraints(g_target * MB_UNIT);
    } else {
        /* baseline config for level 1 */
        paramValues_t const l1params = cParamsToPVals(ZSTD_getCParams(1, buf.maxBlockSize, ctx.dictSize));
        BMK_benchResult_t testResult;
        BMK_benchParam(&testResult, buf, ctx, l1params);
        BMK_init_level_constraints((int)((testResult.cSpeed * 31) / 32));
    }

    /* populate initial solution */
    {   const int maxSeeds = g_noSeed ? 1 : ZSTD_maxCLevel();
        int i;
        for (i=0; i<=maxSeeds; i++) {
            params = cParamsToPVals(ZSTD_getCParams(i, buf.maxBlockSize, 0));
            BMK_seed(winners, params, buf, ctx);
    }   }
    BMK_saveAndPrint_cLevelTable(f, winners, buf.srcSize);

    /* start tests */
    {   const UTIL_time_t grillStart = UTIL_getTime();
        do {
            BMK_selectRandomStart(f, winners, buf, ctx);
        } while (BMK_timeSpan_s(grillStart) < g_timeLimit_s);
    }

    /* end summary */
    BMK_saveAndPrint_cLevelTable(f, winners, buf.srcSize);
    DISPLAY("grillParams operations completed \n");

    /* clean up*/
    fclose(f);
}