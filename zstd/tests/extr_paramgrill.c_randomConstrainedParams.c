#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t varInds_t ;
struct TYPE_7__ {size_t* vals; } ;
typedef  TYPE_1__ paramValues_t ;
struct TYPE_8__ {size_t tableLen; size_t* varArray; } ;
typedef  TYPE_2__ memoTable_t ;
typedef  size_t ZSTD_strategy ;

/* Variables and functions */
 int FUZ_rand (int /*<<< orphan*/ *) ; 
 int NUM_PARAMS ; 
 int /*<<< orphan*/  g_rand ; 
 int /*<<< orphan*/  memoTableGet (TYPE_2__ const*,TYPE_1__) ; 
 size_t rangeMap (size_t,int) ; 
 int* rangetable ; 
 size_t strt_ind ; 

__attribute__((used)) static void randomConstrainedParams(paramValues_t* pc, const memoTable_t* memoTableArray, const ZSTD_strategy st)
{
    size_t j;
    const memoTable_t mt = memoTableArray[st];
    pc->vals[strt_ind] = st;
    for(j = 0; j < mt.tableLen; j++) {
        int i;
        for(i = 0; i < NUM_PARAMS; i++) {
            varInds_t v = mt.varArray[i];
            if(v == strt_ind) continue;
            pc->vals[v] = rangeMap(v, FUZ_rand(&g_rand) % rangetable[v]);
        }

        if(!(memoTableGet(memoTableArray, *pc))) break; /* only pick unpicked params. */
    }
}