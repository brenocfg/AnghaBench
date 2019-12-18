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
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  sa_share_t ;
typedef  int /*<<< orphan*/  sa_share_impl_t ;
typedef  int /*<<< orphan*/  sa_handle_t ;
typedef  int /*<<< orphan*/  sa_handle_impl_t ;
typedef  int /*<<< orphan*/  sa_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int process_share (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int
sa_zfs_process_share(sa_handle_t handle, sa_group_t group, sa_share_t share,
    char *mountpoint, char *proto, zprop_source_t source, char *shareopts,
    char *sourcestr, char *dataset)
{
	sa_handle_impl_t impl_handle = (sa_handle_impl_t)handle;
	sa_share_impl_t impl_share = (sa_share_impl_t)share;

	return (process_share(impl_handle, impl_share, mountpoint, NULL,
	    proto, shareopts, NULL, dataset, B_FALSE));
}