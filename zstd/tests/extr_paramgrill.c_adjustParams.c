#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t varInds_t ;
struct TYPE_6__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;

/* Variables and functions */
 size_t NUM_PARAMS ; 
 int /*<<< orphan*/  ZSTD_adjustCParams (int /*<<< orphan*/ ,size_t const,size_t const) ; 
 TYPE_1__ cParamsToPVals (int /*<<< orphan*/ ) ; 
 size_t fadt_ind ; 
 int /*<<< orphan*/  pvalsToCParams (TYPE_1__) ; 
 size_t strt_ind ; 

__attribute__((used)) static paramValues_t
adjustParams(paramValues_t p, const size_t maxBlockSize, const size_t dictSize)
{
    paramValues_t ot = p;
    varInds_t i;
    p = cParamsToPVals(ZSTD_adjustCParams(pvalsToCParams(p), maxBlockSize, dictSize));
    if (!dictSize) { p.vals[fadt_ind] = 0; }
    /* retain value of all other parameters */
    for(i = strt_ind + 1; i < NUM_PARAMS; i++) {
        p.vals[i] = ot.vals[i];
    }
    return p;
}