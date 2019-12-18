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
typedef  int boolean_t ;

/* Variables and functions */
 unsigned int ZFS_PROP_USEROBJQUOTA ; 
 unsigned int ZFS_PROP_USEROBJUSED ; 
 unsigned int ZFS_PROP_USERQUOTA ; 
 unsigned int ZFS_PROP_USERUSED ; 

__attribute__((used)) static boolean_t
zfs_prop_is_user(unsigned p)
{
	return (p == ZFS_PROP_USERUSED || p == ZFS_PROP_USERQUOTA ||
	    p == ZFS_PROP_USEROBJUSED || p == ZFS_PROP_USEROBJQUOTA);
}