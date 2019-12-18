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
struct stack {int size; void** item; } ;

/* Variables and functions */
 scalar_t__ redcarpet_stack_grow (struct stack*,int) ; 

int
redcarpet_stack_push(struct stack *st, void *item)
{
	if (redcarpet_stack_grow(st, st->size * 2) < 0)
		return -1;

	st->item[st->size++] = item;
	return 0;
}