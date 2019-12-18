#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tqent_flags; int /*<<< orphan*/ * tqent_arg; int /*<<< orphan*/ * tqent_func; int /*<<< orphan*/ * tqent_prev; int /*<<< orphan*/ * tqent_next; } ;
typedef  TYPE_1__ taskq_ent_t ;

/* Variables and functions */

void
taskq_init_ent(taskq_ent_t *t)
{
	t->tqent_next = NULL;
	t->tqent_prev = NULL;
	t->tqent_func = NULL;
	t->tqent_arg = NULL;
	t->tqent_flags = 0;
}