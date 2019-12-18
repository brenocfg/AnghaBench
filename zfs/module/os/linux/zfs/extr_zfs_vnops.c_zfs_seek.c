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
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ offset_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAXOFFSET_T ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 

int
zfs_seek(struct inode *ip, offset_t ooff, offset_t *noffp)
{
	if (S_ISDIR(ip->i_mode))
		return (0);
	return ((*noffp < 0 || *noffp > MAXOFFSET_T) ? EINVAL : 0);
}