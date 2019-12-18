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
struct stack {scalar_t__ asize; scalar_t__ size; int /*<<< orphan*/ * item; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
redcarpet_stack_free(struct stack *st)
{
	if (!st)
		return;

	free(st->item);

	st->item = NULL;
	st->size = 0;
	st->asize = 0;
}