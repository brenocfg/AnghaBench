#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sa_share_impl_t ;
struct TYPE_8__ {char* security; void* cookie; int /*<<< orphan*/  sharepath; int /*<<< orphan*/  callback; } ;
typedef  TYPE_2__ nfs_host_cookie_t ;
typedef  int /*<<< orphan*/  nfs_host_callback_t ;
struct TYPE_9__ {char* shareopts; } ;
struct TYPE_7__ {int /*<<< orphan*/  sharepath; } ;

/* Variables and functions */
 TYPE_5__* FSINFO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_nfs_host_cb ; 
 int foreach_nfs_shareopt (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_fstype ; 

__attribute__((used)) static int
foreach_nfs_host(sa_share_impl_t impl_share, nfs_host_callback_t callback,
    void *cookie)
{
	nfs_host_cookie_t udata;
	char *shareopts;

	udata.callback = callback;
	udata.sharepath = impl_share->sharepath;
	udata.cookie = cookie;
	udata.security = "sys";

	shareopts = FSINFO(impl_share, nfs_fstype)->shareopts;

	return foreach_nfs_shareopt(shareopts, foreach_nfs_host_cb,
	    &udata);
}