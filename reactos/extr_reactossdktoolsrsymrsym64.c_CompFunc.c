#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ FunctionStart; } ;
typedef  TYPE_1__* PRUNTIME_FUNCTION ;

/* Variables and functions */

int CompFunc(const void *p1, const void *p2)
{
    PRUNTIME_FUNCTION prf1 = (void*)p1, prf2 = (void*)p2;
    return (prf1->FunctionStart > prf2->FunctionStart ? 1 : -1);
}