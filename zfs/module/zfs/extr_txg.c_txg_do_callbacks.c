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
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_tx_do_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
txg_do_callbacks(list_t *cb_list)
{
	dmu_tx_do_callbacks(cb_list, 0);

	list_destroy(cb_list);

	kmem_free(cb_list, sizeof (list_t));
}