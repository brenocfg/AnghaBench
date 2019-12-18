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
 unsigned int ZFS_PROP_PROJECTOBJQUOTA ; 
 unsigned int ZFS_PROP_PROJECTOBJUSED ; 
 unsigned int ZFS_PROP_PROJECTQUOTA ; 
 unsigned int ZFS_PROP_PROJECTUSED ; 

__attribute__((used)) static boolean_t
zfs_prop_is_project(unsigned p)
{
	return (p == ZFS_PROP_PROJECTUSED || p == ZFS_PROP_PROJECTQUOTA ||
	    p == ZFS_PROP_PROJECTOBJUSED || p == ZFS_PROP_PROJECTOBJQUOTA);
}