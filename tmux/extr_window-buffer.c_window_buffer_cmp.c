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
struct window_buffer_itemdata {int order; int size; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ field; scalar_t__ reversed; } ;

/* Variables and functions */
 scalar_t__ WINDOW_BUFFER_BY_SIZE ; 
 scalar_t__ WINDOW_BUFFER_BY_TIME ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* window_buffer_sort ; 

__attribute__((used)) static int
window_buffer_cmp(const void *a0, const void *b0)
{
	const struct window_buffer_itemdata *const	*a = a0;
	const struct window_buffer_itemdata *const	*b = b0;
	int						 result = 0;

	if (window_buffer_sort->field == WINDOW_BUFFER_BY_TIME)
		result = (*b)->order - (*a)->order;
	else if (window_buffer_sort->field == WINDOW_BUFFER_BY_SIZE)
		result = (*b)->size - (*a)->size;

	/* Use WINDOW_BUFFER_BY_NAME as default order and tie breaker. */
	if (result == 0)
		result = strcmp((*a)->name, (*b)->name);

	if (window_buffer_sort->reversed)
		result = -result;
	return (result);
}