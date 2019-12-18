#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ddt_repair_tree; int /*<<< orphan*/  ddt_spa; } ;
typedef  TYPE_1__ ddt_t ;
struct TYPE_11__ {int /*<<< orphan*/ * dde_repair_abd; } ;
typedef  TYPE_2__ ddt_entry_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddt_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  ddt_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  ddt_free (TYPE_2__*) ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ ) ; 

void
ddt_repair_done(ddt_t *ddt, ddt_entry_t *dde)
{
	avl_index_t where;

	ddt_enter(ddt);

	if (dde->dde_repair_abd != NULL && spa_writeable(ddt->ddt_spa) &&
	    avl_find(&ddt->ddt_repair_tree, dde, &where) == NULL)
		avl_insert(&ddt->ddt_repair_tree, dde, where);
	else
		ddt_free(dde);

	ddt_exit(ddt);
}