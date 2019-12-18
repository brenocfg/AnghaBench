#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa_share_impl_t ;
struct TYPE_2__ {int /*<<< orphan*/ * shareopts; } ;

/* Variables and functions */
 TYPE_1__* FSINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_fstype ; 

__attribute__((used)) static void
nfs_clear_shareopts(sa_share_impl_t impl_share)
{
	free(FSINFO(impl_share, nfs_fstype)->shareopts);
	FSINFO(impl_share, nfs_fstype)->shareopts = NULL;
}