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
typedef  int /*<<< orphan*/  rrwlock_t ;
struct TYPE_4__ {void* rn_tag; int /*<<< orphan*/  rn_next; int /*<<< orphan*/ * rn_rrl; } ;
typedef  TYPE_1__ rrw_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_tsd_key ; 
 int /*<<< orphan*/  tsd_get (int /*<<< orphan*/ ) ; 
 scalar_t__ tsd_set (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
rrn_add(rrwlock_t *rrl, void *tag)
{
	rrw_node_t *rn;

	rn = kmem_alloc(sizeof (*rn), KM_SLEEP);
	rn->rn_rrl = rrl;
	rn->rn_next = tsd_get(rrw_tsd_key);
	rn->rn_tag = tag;
	VERIFY(tsd_set(rrw_tsd_key, rn) == 0);
}