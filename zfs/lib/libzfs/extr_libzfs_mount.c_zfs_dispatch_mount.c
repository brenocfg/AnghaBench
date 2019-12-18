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
typedef  int /*<<< orphan*/  zfs_iter_f ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  tpool_t ;
struct TYPE_3__ {size_t mnt_num_handles; int mnt_idx; void* mnt_data; int /*<<< orphan*/  mnt_func; int /*<<< orphan*/ ** mnt_zhps; int /*<<< orphan*/ * mnt_tp; int /*<<< orphan*/ * mnt_hdl; } ;
typedef  TYPE_1__ mnt_param_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  tpool_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_mount_task ; 

__attribute__((used)) static void
zfs_dispatch_mount(libzfs_handle_t *hdl, zfs_handle_t **handles,
    size_t num_handles, int idx, zfs_iter_f func, void *data, tpool_t *tp)
{
	mnt_param_t *mnt_param = zfs_alloc(hdl, sizeof (mnt_param_t));

	mnt_param->mnt_hdl = hdl;
	mnt_param->mnt_tp = tp;
	mnt_param->mnt_zhps = handles;
	mnt_param->mnt_num_handles = num_handles;
	mnt_param->mnt_idx = idx;
	mnt_param->mnt_func = func;
	mnt_param->mnt_data = data;

	(void) tpool_dispatch(tp, zfs_mount_task, (void*)mnt_param);
}