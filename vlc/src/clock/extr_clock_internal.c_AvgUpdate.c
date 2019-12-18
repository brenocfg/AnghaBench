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
struct TYPE_3__ {int count; int range; int value; } ;
typedef  TYPE_1__ average_t ;

/* Variables and functions */

void AvgUpdate(average_t *avg, double value)
{
    const int new_value_weight = 1;
    int average_weight;
    int divider;
    if (avg->count < avg->range)
    {
        average_weight = avg->count++;
        divider = avg->count;
    }
    else
    {
        average_weight = avg->range - 1;
        divider = avg->range;
    }

    const double tmp = average_weight * avg->value + new_value_weight * value;
    avg->value = tmp / divider;
}