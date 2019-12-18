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
struct nfs_context {int dummy; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {void* p_nfsdir; struct nfs_context* p_nfs; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ NFS_CHECK_STATUS (TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  VLC_UNUSED (struct nfs_context*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
nfs_opendir_cb(int i_status, struct nfs_context *p_nfs, void *p_data,
               void *p_private_data)
{
    VLC_UNUSED(p_nfs);
    stream_t *p_access = p_private_data;
    access_sys_t *p_sys = p_access->p_sys;
    assert(p_sys->p_nfs == p_nfs);
    if (NFS_CHECK_STATUS(p_access, i_status, p_data))
        return;

    p_sys->p_nfsdir = p_data;
}