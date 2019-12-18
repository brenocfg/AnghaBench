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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_NICENUM_TIME ; 
 int /*<<< orphan*/  zfs_nicenum_format (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

void
zfs_nicetime(uint64_t num, char *buf, size_t buflen)
{
	zfs_nicenum_format(num, buf, buflen, ZFS_NICENUM_TIME);
}