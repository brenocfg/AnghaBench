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
struct window_client_itemdata {TYPE_2__* c; } ;
struct TYPE_3__ {scalar_t__ sx; scalar_t__ sy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__ tty; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
window_client_cmp_size(const void *a0, const void *b0)
{
	const struct window_client_itemdata *const *a = a0;
	const struct window_client_itemdata *const *b = b0;

	if ((*a)->c->tty.sx < (*b)->c->tty.sx)
		return (-1);
	if ((*a)->c->tty.sx > (*b)->c->tty.sx)
		return (1);
	if ((*a)->c->tty.sy < (*b)->c->tty.sy)
		return (-1);
	if ((*a)->c->tty.sy > (*b)->c->tty.sy)
		return (1);
	return (strcmp((*a)->c->name, (*b)->c->name));
}