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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  txg_node_t ;
struct TYPE_3__ {char* tl_offset; int /*<<< orphan*/  tl_spa; int /*<<< orphan*/  tl_lock; int /*<<< orphan*/ ** tl_head; } ;
typedef  TYPE_1__ txg_list_t ;

/* Variables and functions */
 int TXG_MASK ; 
 int /*<<< orphan*/  TXG_VERIFY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void *
txg_list_head(txg_list_t *tl, uint64_t txg)
{
	int t = txg & TXG_MASK;
	txg_node_t *tn;

	mutex_enter(&tl->tl_lock);
	tn = tl->tl_head[t];
	mutex_exit(&tl->tl_lock);

	TXG_VERIFY(tl->tl_spa, txg);
	return (tn == NULL ? NULL : (char *)tn - tl->tl_offset);
}