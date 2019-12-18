#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ddt_lock; int /*<<< orphan*/  ddt_repair_tree; int /*<<< orphan*/  ddt_tree; } ;
typedef  TYPE_1__ ddt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ddt_table_free(ddt_t *ddt)
{
	ASSERT(avl_numnodes(&ddt->ddt_tree) == 0);
	ASSERT(avl_numnodes(&ddt->ddt_repair_tree) == 0);
	avl_destroy(&ddt->ddt_tree);
	avl_destroy(&ddt->ddt_repair_tree);
	mutex_destroy(&ddt->ddt_lock);
	kmem_cache_free(ddt_cache, ddt);
}