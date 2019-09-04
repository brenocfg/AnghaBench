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
typedef  int uint64_t ;
struct bintime {int sec; int frac; } ;

/* Variables and functions */
 int abs_to_nanos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

void binuptime(struct bintime *bt) {
  uint64_t ns;
  
  ns = abs_to_nanos(mach_absolute_time());

  bt->sec = (ns / 1000000000);
  bt->frac = (((ns % 1000000000) * (((uint64_t) 1 << 63) / 500000000)));
}