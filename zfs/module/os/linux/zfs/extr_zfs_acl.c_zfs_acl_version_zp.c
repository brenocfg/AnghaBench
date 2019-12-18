#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
struct TYPE_2__ {int /*<<< orphan*/  z_version; } ;

/* Variables and functions */
 TYPE_1__* ZTOZSB (int /*<<< orphan*/ *) ; 
 int zfs_acl_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_acl_version_zp(znode_t *zp)
{
	return (zfs_acl_version(ZTOZSB(zp)->z_version));
}