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
 int redcarpet_stack_grow (struct stack*,size_t) ; 

int
redcarpet_stack_init(struct stack *st, size_t initial_size)
{
	st->item = NULL;
	st->size = 0;
	st->asize = 0;

	if (!initial_size)
		initial_size = 8;

	return redcarpet_stack_grow(st, initial_size);
}