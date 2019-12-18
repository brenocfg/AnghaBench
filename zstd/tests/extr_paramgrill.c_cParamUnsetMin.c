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
typedef  size_t varInds_t ;
struct TYPE_4__ {scalar_t__* vals; } ;
typedef  TYPE_1__ paramValues_t ;

/* Variables and functions */
 size_t NUM_PARAMS ; 
 scalar_t__ PARAM_UNSET ; 
 scalar_t__* mintable ; 

__attribute__((used)) static paramValues_t cParamUnsetMin(paramValues_t paramTarget)
{
    varInds_t vi;
    for (vi = 0; vi < NUM_PARAMS; vi++) {
        if (paramTarget.vals[vi] == PARAM_UNSET) {
            paramTarget.vals[vi] = mintable[vi];
        }
    }
    return paramTarget;
}