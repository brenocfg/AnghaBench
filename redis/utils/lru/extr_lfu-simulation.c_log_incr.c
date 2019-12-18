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
typedef  int uint8_t ;

/* Variables and functions */
 int COUNTER_INIT_VAL ; 
 double RAND_MAX ; 
 scalar_t__ rand () ; 

uint8_t log_incr(uint8_t counter) {
    if (counter == 255) return counter;
    double r = (double)rand()/RAND_MAX;
    double baseval = counter-COUNTER_INIT_VAL;
    if (baseval < 0) baseval = 0;
    double limit = 1.0/(baseval*10+1);
    if (r < limit) counter++;
    return counter;
}