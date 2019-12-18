#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_5__ {int /*<<< orphan*/  dcb_data; int /*<<< orphan*/  (* dcb_func ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ dmu_tx_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void
dmu_tx_do_callbacks(list_t *cb_list, int error)
{
	dmu_tx_callback_t *dcb;

	while ((dcb = list_tail(cb_list)) != NULL) {
		list_remove(cb_list, dcb);
		dcb->dcb_func(dcb->dcb_data, error);
		kmem_free(dcb, sizeof (dmu_tx_callback_t));
	}
}