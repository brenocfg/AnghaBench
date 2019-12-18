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
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_5__ {TYPE_1__* td_pfd; int /*<<< orphan*/  td_rootbp; int /*<<< orphan*/  td_objset; int /*<<< orphan*/ * td_resume; TYPE_1__* td_arg; int /*<<< orphan*/  td_func; } ;
typedef  TYPE_2__ traverse_data_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
struct TYPE_4__ {int /*<<< orphan*/  pd_mtx; int /*<<< orphan*/  pd_cv; int /*<<< orphan*/  pd_exited; int /*<<< orphan*/  pd_resume; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZB_ROOT_BLKID ; 
 int /*<<< orphan*/  ZB_ROOT_LEVEL ; 
 int /*<<< orphan*/  ZB_ROOT_OBJECT ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_prefetcher ; 
 int /*<<< orphan*/  traverse_visitbp (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
traverse_prefetch_thread(void *arg)
{
	traverse_data_t *td_main = arg;
	traverse_data_t td = *td_main;
	zbookmark_phys_t czb;
	fstrans_cookie_t cookie = spl_fstrans_mark();

	td.td_func = traverse_prefetcher;
	td.td_arg = td_main->td_pfd;
	td.td_pfd = NULL;
	td.td_resume = &td_main->td_pfd->pd_resume;

	SET_BOOKMARK(&czb, td.td_objset,
	    ZB_ROOT_OBJECT, ZB_ROOT_LEVEL, ZB_ROOT_BLKID);
	(void) traverse_visitbp(&td, NULL, td.td_rootbp, &czb);

	mutex_enter(&td_main->td_pfd->pd_mtx);
	td_main->td_pfd->pd_exited = B_TRUE;
	cv_broadcast(&td_main->td_pfd->pd_cv);
	mutex_exit(&td_main->td_pfd->pd_mtx);
	spl_fstrans_unmark(cookie);
}