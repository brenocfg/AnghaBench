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
struct TYPE_4__ {scalar_t__ zcw_zio_error; int /*<<< orphan*/  zcw_done; int /*<<< orphan*/ * zcw_lwb; int /*<<< orphan*/  zcw_node; int /*<<< orphan*/  zcw_lock; int /*<<< orphan*/  zcw_cv; } ;
typedef  TYPE_1__ zil_commit_waiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_link_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_zcw_cache ; 

__attribute__((used)) static zil_commit_waiter_t *
zil_alloc_commit_waiter(void)
{
	zil_commit_waiter_t *zcw = kmem_cache_alloc(zil_zcw_cache, KM_SLEEP);

	cv_init(&zcw->zcw_cv, NULL, CV_DEFAULT, NULL);
	mutex_init(&zcw->zcw_lock, NULL, MUTEX_DEFAULT, NULL);
	list_link_init(&zcw->zcw_node);
	zcw->zcw_lwb = NULL;
	zcw->zcw_done = B_FALSE;
	zcw->zcw_zio_error = 0;

	return (zcw);
}