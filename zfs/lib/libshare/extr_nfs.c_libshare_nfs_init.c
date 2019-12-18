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

/* Variables and functions */
 int /*<<< orphan*/  nfs_fstype ; 
 int /*<<< orphan*/  nfs_shareops ; 
 int /*<<< orphan*/  register_fstype (char*,int /*<<< orphan*/ *) ; 

void
libshare_nfs_init(void)
{
	nfs_fstype = register_fstype("nfs", &nfs_shareops);
}