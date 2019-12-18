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
typedef  int uint_t ;

/* Variables and functions */
 int KM_NOSLEEP ; 
 int KM_PUSHPAGE ; 
 int KM_SLEEP ; 
 int TQ_NOSLEEP ; 
 int TQ_PUSHPAGE ; 

__attribute__((used)) static int
task_km_flags(uint_t flags)
{
	if (flags & TQ_NOSLEEP)
		return (KM_NOSLEEP);

	if (flags & TQ_PUSHPAGE)
		return (KM_PUSHPAGE);

	return (KM_SLEEP);
}