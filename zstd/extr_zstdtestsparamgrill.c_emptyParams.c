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
struct TYPE_3__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;
typedef  size_t U32 ;

/* Variables and functions */
 size_t NUM_PARAMS ; 
 int /*<<< orphan*/  PARAM_UNSET ; 

__attribute__((used)) static paramValues_t emptyParams(void)
{
    U32 i;
    paramValues_t p;
    for(i = 0; i < NUM_PARAMS; i++) {
        p.vals[i] = PARAM_UNSET;
    }
    return p;
}