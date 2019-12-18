#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BMK_timedFnState_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_resetTimedFnState (int /*<<< orphan*/ * const,unsigned int,unsigned int) ; 
 scalar_t__ malloc (int) ; 

BMK_timedFnState_t* BMK_createTimedFnState(unsigned total_ms, unsigned run_ms)
{
    BMK_timedFnState_t* const r = (BMK_timedFnState_t*)malloc(sizeof(*r));
    if (r == NULL) return NULL;   /* malloc() error */
    BMK_resetTimedFnState(r, total_ms, run_ms);
    return r;
}