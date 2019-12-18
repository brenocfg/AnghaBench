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
typedef  int /*<<< orphan*/  zfs_handle_t ;

/* Variables and functions */
 int parent_name (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 

int
zfs_parent_name(zfs_handle_t *zhp, char *buf, size_t buflen)
{
	return (parent_name(zfs_get_name(zhp), buf, buflen));
}