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
struct TYPE_3__ {int /*<<< orphan*/  l_dbuf; int /*<<< orphan*/  l_rwlock; } ;
typedef  TYPE_1__ zap_leaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

void
zap_put_leaf(zap_leaf_t *l)
{
	rw_exit(&l->l_rwlock);
	dmu_buf_rele(l->l_dbuf, NULL);
}