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
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkptr_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZB_DESTROYED_OBJSET ; 
 int traverse_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 

int
traverse_dataset_destroyed(spa_t *spa, blkptr_t *blkptr,
    uint64_t txg_start, zbookmark_phys_t *resume, int flags,
    blkptr_cb_t func, void *arg)
{
	return (traverse_impl(spa, NULL, ZB_DESTROYED_OBJSET,
	    blkptr, txg_start, resume, flags, func, arg));
}