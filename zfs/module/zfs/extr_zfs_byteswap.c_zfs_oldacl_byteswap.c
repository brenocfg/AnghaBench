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
typedef  int /*<<< orphan*/  ace_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_oldace_byteswap (int /*<<< orphan*/ *,int) ; 

void
zfs_oldacl_byteswap(void *buf, size_t size)
{
	int cnt;

	/*
	 * Arggh, since we don't know how many ACEs are in
	 * the array, we have to swap the entire block
	 */

	cnt = size / sizeof (ace_t);

	zfs_oldace_byteswap((ace_t *)buf, cnt);
}