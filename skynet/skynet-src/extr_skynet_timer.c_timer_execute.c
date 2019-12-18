#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_node {int dummy; } ;
struct timer {int time; TYPE_2__* near; } ;
struct TYPE_3__ {scalar_t__ next; } ;
struct TYPE_4__ {TYPE_1__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIN_LOCK (struct timer*) ; 
 int /*<<< orphan*/  SPIN_UNLOCK (struct timer*) ; 
 int TIME_NEAR_MASK ; 
 int /*<<< orphan*/  dispatch_list (struct timer_node*) ; 
 struct timer_node* link_clear (TYPE_2__*) ; 

__attribute__((used)) static inline void
timer_execute(struct timer *T) {
	int idx = T->time & TIME_NEAR_MASK;
	
	while (T->near[idx].head.next) {
		struct timer_node *current = link_clear(&T->near[idx]);
		SPIN_UNLOCK(T);
		// dispatch_list don't need lock T
		dispatch_list(current);
		SPIN_LOCK(T);
	}
}