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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  tl_lock; } ;
typedef  TYPE_1__ txg_list_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_list_empty_impl (TYPE_1__*,int /*<<< orphan*/ ) ; 

boolean_t
txg_list_empty(txg_list_t *tl, uint64_t txg)
{
	mutex_enter(&tl->tl_lock);
	boolean_t ret = txg_list_empty_impl(tl, txg);
	mutex_exit(&tl->tl_lock);

	return (ret);
}