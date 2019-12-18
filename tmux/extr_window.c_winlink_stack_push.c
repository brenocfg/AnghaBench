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
struct winlink_stack {int dummy; } ;
struct winlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct winlink_stack*,struct winlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentry ; 
 int /*<<< orphan*/  winlink_stack_remove (struct winlink_stack*,struct winlink*) ; 

void
winlink_stack_push(struct winlink_stack *stack, struct winlink *wl)
{
	if (wl == NULL)
		return;

	winlink_stack_remove(stack, wl);
	TAILQ_INSERT_HEAD(stack, wl, sentry);
}