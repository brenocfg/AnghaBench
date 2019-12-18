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
struct cstate {int /*<<< orphan*/  pend; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/ * y; int /*<<< orphan*/  x; scalar_t__ n; scalar_t__ m; scalar_t__ ng; scalar_t__ c; int /*<<< orphan*/ * cc; } ;
typedef  TYPE_1__ Renode ;

/* Variables and functions */

__attribute__((used)) static Renode *newnode(struct cstate *g, int type)
{
	Renode *node = g->pend++;
	node->type = type;
	node->cc = NULL;
	node->c = 0;
	node->ng = 0;
	node->m = 0;
	node->n = 0;
	node->x = node->y = NULL;
	return node;
}