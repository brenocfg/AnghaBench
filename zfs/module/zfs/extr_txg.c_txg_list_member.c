#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {scalar_t__* tn_member; } ;
typedef  TYPE_1__ txg_node_t ;
struct TYPE_5__ {int tl_offset; int /*<<< orphan*/  tl_spa; } ;
typedef  TYPE_2__ txg_list_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int TXG_MASK ; 
 int /*<<< orphan*/  TXG_VERIFY (int /*<<< orphan*/ ,int) ; 

boolean_t
txg_list_member(txg_list_t *tl, void *p, uint64_t txg)
{
	int t = txg & TXG_MASK;
	txg_node_t *tn = (txg_node_t *)((char *)p + tl->tl_offset);

	TXG_VERIFY(tl->tl_spa, txg);
	return (tn->tn_member[t] != 0);
}