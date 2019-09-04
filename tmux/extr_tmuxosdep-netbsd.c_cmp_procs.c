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
struct kinfo_proc2 {scalar_t__ p_estcpu; scalar_t__ p_slptime; scalar_t__ p_pid; } ;

/* Variables and functions */
 scalar_t__ is_runnable (struct kinfo_proc2*) ; 
 scalar_t__ is_stopped (struct kinfo_proc2*) ; 

struct kinfo_proc2 *
cmp_procs(struct kinfo_proc2 *p1, struct kinfo_proc2 *p2)
{
	if (is_runnable(p1) && !is_runnable(p2))
		return (p1);
	if (!is_runnable(p1) && is_runnable(p2))
		return (p2);

	if (is_stopped(p1) && !is_stopped(p2))
		return (p1);
	if (!is_stopped(p1) && is_stopped(p2))
		return (p2);

	if (p1->p_estcpu > p2->p_estcpu)
		return (p1);
	if (p1->p_estcpu < p2->p_estcpu)
		return (p2);

	if (p1->p_slptime < p2->p_slptime)
		return (p1);
	if (p1->p_slptime > p2->p_slptime)
		return (p2);

	if (p1->p_pid > p2->p_pid)
		return (p1);
	return (p2);
}