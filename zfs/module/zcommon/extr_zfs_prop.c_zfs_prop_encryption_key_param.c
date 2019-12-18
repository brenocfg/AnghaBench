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
typedef  scalar_t__ zfs_prop_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ ZFS_PROP_KEYFORMAT ; 
 scalar_t__ ZFS_PROP_PBKDF2_ITERS ; 
 scalar_t__ ZFS_PROP_PBKDF2_SALT ; 

boolean_t
zfs_prop_encryption_key_param(zfs_prop_t prop)
{
	/*
	 * keylocation does not count as an encryption property. It can be
	 * changed at will without needing the master keys.
	 */
	return (prop == ZFS_PROP_PBKDF2_SALT || prop == ZFS_PROP_PBKDF2_ITERS ||
	    prop == ZFS_PROP_KEYFORMAT);
}