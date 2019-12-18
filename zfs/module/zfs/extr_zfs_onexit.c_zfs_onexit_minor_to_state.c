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
typedef  int /*<<< orphan*/  zfs_onexit_t ;
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZST_ONEXIT ; 
 int /*<<< orphan*/ * zfsdev_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_onexit_minor_to_state(minor_t minor, zfs_onexit_t **zo)
{
	*zo = zfsdev_get_state(minor, ZST_ONEXIT);
	if (*zo == NULL)
		return (SET_ERROR(EBADF));

	return (0);
}