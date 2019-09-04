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
struct kinfo_proc {scalar_t__ ki_estcpu; scalar_t__ ki_slptime; scalar_t__ ki_pid; int /*<<< orphan*/  ki_comm; } ;

/* Variables and functions */
 scalar_t__ is_runnable (struct kinfo_proc*) ; 
 scalar_t__ is_stopped (struct kinfo_proc*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct kinfo_proc *
cmp_procs(struct kinfo_proc *p1, struct kinfo_proc *p2)
{
	if (is_runnable(p1) && !is_runnable(p2))
		return (p1);
	if (!is_runnable(p1) && is_runnable(p2))
		return (p2);

	if (is_stopped(p1) && !is_stopped(p2))
		return (p1);
	if (!is_stopped(p1) && is_stopped(p2))
		return (p2);

	if (p1->ki_estcpu > p2->ki_estcpu)
		return (p1);
	if (p1->ki_estcpu < p2->ki_estcpu)
		return (p2);

	if (p1->ki_slptime < p2->ki_slptime)
		return (p1);
	if (p1->ki_slptime > p2->ki_slptime)
		return (p2);

	if (strcmp(p1->ki_comm, p2->ki_comm) < 0)
		return (p1);
	if (strcmp(p1->ki_comm, p2->ki_comm) > 0)
		return (p2);

	if (p1->ki_pid > p2->ki_pid)
		return (p1);
	return (p2);
}