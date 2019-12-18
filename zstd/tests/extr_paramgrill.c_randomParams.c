#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t varInds_t ;
struct TYPE_3__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;

/* Variables and functions */
 int FUZ_rand (int /*<<< orphan*/ *) ; 
 size_t NUM_PARAMS ; 
 int /*<<< orphan*/  g_rand ; 
 int /*<<< orphan*/  rangeMap (size_t,int) ; 
 int* rangetable ; 

__attribute__((used)) static paramValues_t randomParams(void)
{
    varInds_t v; paramValues_t p;
    for(v = 0; v < NUM_PARAMS; v++) {
        p.vals[v] = rangeMap(v, (int)(FUZ_rand(&g_rand) % rangetable[v]));
    }
    return p;
}