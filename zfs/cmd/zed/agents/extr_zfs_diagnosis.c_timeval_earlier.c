#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ertv_sec; scalar_t__ ertv_nsec; } ;
typedef  TYPE_1__ er_timeval_t ;
typedef  int boolean_t ;

/* Variables and functions */

__attribute__((used)) static boolean_t
timeval_earlier(er_timeval_t *a, er_timeval_t *b)
{
	return (a->ertv_sec < b->ertv_sec ||
	    (a->ertv_sec == b->ertv_sec && a->ertv_nsec < b->ertv_nsec));
}