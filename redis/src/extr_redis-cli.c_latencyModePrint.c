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
struct TYPE_2__ {scalar_t__ output; } ;

/* Variables and functions */
 scalar_t__ OUTPUT_CSV ; 
 scalar_t__ OUTPUT_RAW ; 
 scalar_t__ OUTPUT_STANDARD ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,long long,long long,double,long long) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void latencyModePrint(long long min, long long max, double avg, long long count) {
    if (config.output == OUTPUT_STANDARD) {
        printf("min: %lld, max: %lld, avg: %.2f (%lld samples)",
                min, max, avg, count);
        fflush(stdout);
    } else if (config.output == OUTPUT_CSV) {
        printf("%lld,%lld,%.2f,%lld\n", min, max, avg, count);
    } else if (config.output == OUTPUT_RAW) {
        printf("%lld %lld %.2f %lld\n", min, max, avg, count);
    }
}