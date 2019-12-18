#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* proto; TYPE_2__* handle; } ;
typedef  TYPE_1__ update_cookie_t ;
typedef  TYPE_2__* sa_handle_impl_t ;
struct TYPE_6__ {int /*<<< orphan*/ * zfs_libhandle; } ;

/* Variables and functions */
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 int /*<<< orphan*/  update_zfs_shares_cb ; 
 int /*<<< orphan*/  zfs_iter_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
update_zfs_shares(sa_handle_impl_t impl_handle, const char *proto)
{
	update_cookie_t udata;

	if (impl_handle->zfs_libhandle == NULL)
		return (SA_SYSTEM_ERR);

	udata.handle = impl_handle;
	udata.proto = proto;
	(void) zfs_iter_root(impl_handle->zfs_libhandle, update_zfs_shares_cb,
	    &udata);

	return (SA_OK);
}