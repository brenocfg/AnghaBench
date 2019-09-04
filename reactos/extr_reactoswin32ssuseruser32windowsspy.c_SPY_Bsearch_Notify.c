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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ value; } ;
typedef  TYPE_1__ SPY_NOTIFY ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_1__ const*) ; 
 TYPE_1__ const* spnfy_array ; 

__attribute__((used)) static const SPY_NOTIFY *SPY_Bsearch_Notify( UINT code)
{
    int low = 0, high = ARRAYSIZE(spnfy_array) - 1;

    while (low <= high)
    {
        int idx = (low + high) / 2;
        if (spnfy_array[idx].value == code) return spnfy_array + idx;
        if (spnfy_array[idx].value < code)
            high = idx - 1;
        else
            low = idx + 1;
    }
    return NULL;
}