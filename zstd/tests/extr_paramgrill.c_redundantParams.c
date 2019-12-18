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
struct TYPE_6__ {int* vals; } ;
typedef  TYPE_1__ paramValues_t ;
struct TYPE_7__ {scalar_t__ cMem; } ;
typedef  TYPE_2__ constraint_t ;

/* Variables and functions */
 int ZSTD_btlazy2 ; 
 size_t ZSTD_estimateCStreamSize_usingCParams (int /*<<< orphan*/ ) ; 
 size_t clog_ind ; 
 size_t hlog_ind ; 
 int* mintable ; 
 int /*<<< orphan*/  pvalsToCParams (TYPE_1__ const) ; 
 size_t slog_ind ; 
 size_t strt_ind ; 
 size_t wlog_ind ; 

__attribute__((used)) static int
redundantParams(const paramValues_t paramValues, const constraint_t target, const size_t maxBlockSize)
{
    return
       (ZSTD_estimateCStreamSize_usingCParams(pvalsToCParams(paramValues)) > (size_t)target.cMem) /* Uses too much memory */
    || ((1ULL << (paramValues.vals[wlog_ind] - 1)) >= maxBlockSize && paramValues.vals[wlog_ind] != mintable[wlog_ind]) /* wlog too much bigger than src size */
    || (paramValues.vals[clog_ind] > (paramValues.vals[wlog_ind] + (paramValues.vals[strt_ind] > ZSTD_btlazy2))) /* chainLog larger than windowLog*/
    || (paramValues.vals[slog_ind] > paramValues.vals[clog_ind]) /* searchLog larger than chainLog */
    || (paramValues.vals[hlog_ind] > paramValues.vals[wlog_ind] + 1); /* hashLog larger than windowLog + 1 */
}