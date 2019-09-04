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
struct timeval {long tv_sec; int tv_usec; } ;

/* Variables and functions */
 int abs_to_nanos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

void getmicrotime(struct timeval *tv) {
  uint64_t ns, sns;

  ns = abs_to_nanos(mach_absolute_time());

  sns = (ns / 1000000000);
  tv->tv_sec = (long) sns;
  tv->tv_usec = (int) ((ns - sns) / 1000);
}