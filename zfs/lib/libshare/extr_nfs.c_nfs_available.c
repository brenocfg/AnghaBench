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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  nfs_check_exportfs () ; 
 int nfs_exportfs_temp_fd ; 

__attribute__((used)) static boolean_t
nfs_available(void)
{
	if (nfs_exportfs_temp_fd == -1)
		(void) nfs_check_exportfs();

	return ((nfs_exportfs_temp_fd != -1) ? B_TRUE : B_FALSE);
}