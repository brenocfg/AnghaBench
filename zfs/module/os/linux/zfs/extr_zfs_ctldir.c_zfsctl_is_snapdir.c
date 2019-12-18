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
struct inode {scalar_t__ i_ino; } ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ ZFSCTL_INO_SNAPDIRS ; 
 scalar_t__ zfsctl_is_node (struct inode*) ; 

boolean_t
zfsctl_is_snapdir(struct inode *ip)
{
	return (zfsctl_is_node(ip) && (ip->i_ino <= ZFSCTL_INO_SNAPDIRS));
}