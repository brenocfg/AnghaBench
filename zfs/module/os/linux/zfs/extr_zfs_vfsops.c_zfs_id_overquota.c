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
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ zfs_id_overblockquota (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_id_overobjquota (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
zfs_id_overquota(zfsvfs_t *zfsvfs, uint64_t usedobj, uint64_t id)
{
	return (zfs_id_overblockquota(zfsvfs, usedobj, id) ||
	    zfs_id_overobjquota(zfsvfs, usedobj, id));
}