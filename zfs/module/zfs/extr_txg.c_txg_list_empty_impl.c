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
typedef  size_t uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** tl_head; int /*<<< orphan*/  tl_spa; int /*<<< orphan*/  tl_lock; } ;
typedef  TYPE_1__ txg_list_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  TXG_VERIFY (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static boolean_t
txg_list_empty_impl(txg_list_t *tl, uint64_t txg)
{
	ASSERT(MUTEX_HELD(&tl->tl_lock));
	TXG_VERIFY(tl->tl_spa, txg);
	return (tl->tl_head[txg & TXG_MASK] == NULL);
}