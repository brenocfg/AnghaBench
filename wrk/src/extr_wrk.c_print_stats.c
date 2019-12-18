#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  long double uint64_t ;
struct TYPE_6__ {long double max; } ;
typedef  TYPE_1__ stats ;

/* Variables and functions */
 int /*<<< orphan*/  print_units (long double,char* (*) (long double),int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 long double stats_mean (TYPE_1__*) ; 
 long double stats_stdev (TYPE_1__*,long double) ; 
 char* stats_within_stdev (TYPE_1__*,long double,long double,int) ; 

__attribute__((used)) static void print_stats(char *name, stats *stats, char *(*fmt)(long double)) {
    uint64_t max = stats->max;
    long double mean  = stats_mean(stats);
    long double stdev = stats_stdev(stats, mean);

    printf("    %-10s", name);
    print_units(mean,  fmt, 8);
    print_units(stdev, fmt, 10);
    print_units(max,   fmt, 9);
    printf("%8.2Lf%%\n", stats_within_stdev(stats, mean, stdev, 1));
}