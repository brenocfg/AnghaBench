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
typedef  scalar_t__ time_t ;
typedef  scalar_t__ suseconds_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ USEC_PER_SEC ; 

__attribute__((used)) static void
timeval_normalize(struct timeval *tv, time_t sec, suseconds_t usec)
{
	while (usec >= USEC_PER_SEC) {
		usec -= USEC_PER_SEC;
		sec++;
	}

	while (usec < 0) {
		usec += USEC_PER_SEC;
		sec--;
	}

	tv->tv_sec = sec;
	tv->tv_usec = usec;
}