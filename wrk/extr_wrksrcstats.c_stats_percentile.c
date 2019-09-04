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
struct TYPE_3__ {long double count; size_t min; size_t max; size_t* data; } ;
typedef  TYPE_1__ stats ;

/* Variables and functions */
 size_t round (long double) ; 

uint64_t stats_percentile(stats *stats, long double p) {
    uint64_t rank = round((p / 100.0) * stats->count + 0.5);
    uint64_t total = 0;
    for (uint64_t i = stats->min; i <= stats->max; i++) {
        total += stats->data[i];
        if (total >= rank) return i;
    }
    return 0;
}