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
struct TYPE_3__ {int count; size_t min; size_t max; int* data; } ;
typedef  TYPE_1__ stats ;

/* Variables and functions */
 long double powl (size_t,int) ; 
 long double sqrtl (long double) ; 

long double stats_stdev(stats *stats, long double mean) {
    long double sum = 0.0;
    if (stats->count < 2) return 0.0;
    for (uint64_t i = stats->min; i <= stats->max; i++) {
        if (stats->data[i]) {
            sum += powl(i - mean, 2) * stats->data[i];
        }
    }
    return sqrtl(sum / (stats->count - 1));
}