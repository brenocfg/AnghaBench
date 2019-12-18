#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_6__ {char const* proto; TYPE_3__* handle; } ;
typedef  TYPE_1__ update_cookie_t ;
typedef  TYPE_2__* sa_share_impl_t ;
typedef  TYPE_3__* sa_handle_impl_t ;
struct TYPE_8__ {int /*<<< orphan*/ * zfs_libhandle; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dataset; TYPE_3__* handle; } ;

/* Variables and functions */
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_zfs_shares_cb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
update_zfs_share(sa_share_impl_t impl_share, const char *proto)
{
	sa_handle_impl_t impl_handle = impl_share->handle;
	zfs_handle_t *zhp;
	update_cookie_t udata;

	if (impl_handle->zfs_libhandle == NULL)
			return (SA_SYSTEM_ERR);

	assert(impl_share->dataset != NULL);

	zhp = zfs_open(impl_share->handle->zfs_libhandle, impl_share->dataset,
	    ZFS_TYPE_FILESYSTEM);

	if (zhp == NULL)
		return (SA_SYSTEM_ERR);

	udata.handle = impl_handle;
	udata.proto = proto;
	(void) update_zfs_shares_cb(zhp, &udata);

	return (SA_OK);
}