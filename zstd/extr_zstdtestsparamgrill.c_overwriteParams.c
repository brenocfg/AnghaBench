#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* vals; } ;
typedef  TYPE_1__ paramValues_t ;
typedef  size_t U32 ;

/* Variables and functions */
 size_t NUM_PARAMS ; 
 scalar_t__ PARAM_UNSET ; 

__attribute__((used)) static paramValues_t
overwriteParams(paramValues_t base, const paramValues_t mask)
{
    U32 i;
    for(i = 0; i < NUM_PARAMS; i++) {
        if(mask.vals[i] != PARAM_UNSET) {
            base.vals[i] = mask.vals[i];
        }
    }
    return base;
}