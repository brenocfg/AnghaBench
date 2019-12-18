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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  timeval_normalize (struct timeval*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
timeval_sub(struct timeval *delta, struct timeval *tv1, struct timeval *tv2)
{
	timeval_normalize(delta,
	    tv1->tv_sec - tv2->tv_sec,
	    tv1->tv_usec - tv2->tv_usec);
}