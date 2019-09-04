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
struct window_buffer_itemdata {scalar_t__ order; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
window_buffer_cmp_time(const void *a0, const void *b0)
{
	const struct window_buffer_itemdata *const *a = a0;
	const struct window_buffer_itemdata *const *b = b0;

	if ((*a)->order > (*b)->order)
		return (-1);
	if ((*a)->order < (*b)->order)
		return (1);
	return (strcmp((*a)->name, (*b)->name));
}