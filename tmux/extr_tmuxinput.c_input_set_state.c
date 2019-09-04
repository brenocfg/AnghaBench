#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct window_pane {struct input_ctx* ictx; } ;
struct input_transition {TYPE_1__* state; } ;
struct input_ctx {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enter ) (struct input_ctx*) ;int /*<<< orphan*/  (* exit ) (struct input_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct input_ctx*) ; 
 int /*<<< orphan*/  stub2 (struct input_ctx*) ; 

__attribute__((used)) static void
input_set_state(struct window_pane *wp, const struct input_transition *itr)
{
	struct input_ctx	*ictx = wp->ictx;

	if (ictx->state->exit != NULL)
		ictx->state->exit(ictx);
	ictx->state = itr->state;
	if (ictx->state->enter != NULL)
		ictx->state->enter(ictx);
}