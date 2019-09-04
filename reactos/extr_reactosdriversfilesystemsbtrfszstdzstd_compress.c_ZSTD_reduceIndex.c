#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int hashLog3; int /*<<< orphan*/  hashTable3; int /*<<< orphan*/  chainTable; int /*<<< orphan*/  hashTable; } ;
typedef  TYPE_4__ ZSTD_matchState_t ;
struct TYPE_8__ {int hashLog; scalar_t__ strategy; int chainLog; } ;
struct TYPE_9__ {TYPE_2__ cParams; } ;
struct TYPE_7__ {TYPE_4__ matchState; } ;
struct TYPE_11__ {TYPE_3__ appliedParams; TYPE_1__ blockState; } ;
typedef  TYPE_5__ ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 scalar_t__ ZSTD_btlazy2 ; 
 scalar_t__ ZSTD_fast ; 
 int /*<<< orphan*/  ZSTD_reduceTable (int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  ZSTD_reduceTable_btlazy2 (int /*<<< orphan*/ ,int const,int const) ; 

__attribute__((used)) static void ZSTD_reduceIndex (ZSTD_CCtx* zc, const U32 reducerValue)
{
    ZSTD_matchState_t* const ms = &zc->blockState.matchState;
    {   U32 const hSize = (U32)1 << zc->appliedParams.cParams.hashLog;
        ZSTD_reduceTable(ms->hashTable, hSize, reducerValue);
    }

    if (zc->appliedParams.cParams.strategy != ZSTD_fast) {
        U32 const chainSize = (U32)1 << zc->appliedParams.cParams.chainLog;
        if (zc->appliedParams.cParams.strategy == ZSTD_btlazy2)
            ZSTD_reduceTable_btlazy2(ms->chainTable, chainSize, reducerValue);
        else
            ZSTD_reduceTable(ms->chainTable, chainSize, reducerValue);
    }

    if (ms->hashLog3) {
        U32 const h3Size = (U32)1 << ms->hashLog3;
        ZSTD_reduceTable(ms->hashTable3, h3Size, reducerValue);
    }
}