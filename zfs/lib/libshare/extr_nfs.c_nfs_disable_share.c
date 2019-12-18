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
typedef  int /*<<< orphan*/  sa_share_impl_t ;

/* Variables and functions */
 int SA_OK ; 
 int foreach_nfs_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_available () ; 
 int /*<<< orphan*/  nfs_disable_share_one ; 

__attribute__((used)) static int
nfs_disable_share(sa_share_impl_t impl_share)
{
	if (!nfs_available()) {
		/*
		 * The share can't possibly be active, so nothing
		 * needs to be done to disable it.
		 */
		return (SA_OK);
	}

	return (foreach_nfs_host(impl_share, nfs_disable_share_one, NULL));
}