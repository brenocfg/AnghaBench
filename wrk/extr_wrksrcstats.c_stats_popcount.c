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
typedef  size_t uint64_t ;
struct TYPE_3__ {size_t min; size_t max; scalar_t__* data; } ;
typedef  TYPE_1__ stats ;

/* Variables and functions */

uint64_t stats_popcount(stats *stats) {
    uint64_t count = 0;
    for (uint64_t i = stats->min; i <= stats->max; i++) {
        if (stats->data[i]) count++;
    }
    return count;
}