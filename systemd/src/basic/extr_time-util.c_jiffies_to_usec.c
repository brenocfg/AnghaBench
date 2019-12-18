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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int USEC_PER_SEC ; 
 int sysconf_clock_ticks_cached () ; 

usec_t jiffies_to_usec(uint32_t j) {
        uint32_t hz = sysconf_clock_ticks_cached();
        return DIV_ROUND_UP(j * USEC_PER_SEC, hz);
}