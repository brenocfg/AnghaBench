#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_9__ {int /*<<< orphan*/  dl_name; } ;
typedef  TYPE_2__ zfs_dirlock_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_10__ {scalar_t__ z_case; int /*<<< orphan*/  z_os; scalar_t__ z_norm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MATCH_CASE ; 
 int /*<<< orphan*/  MT_NORMALIZE ; 
 int ZCIEXACT ; 
 int ZCILOOK ; 
 scalar_t__ ZFS_CASE_INSENSITIVE ; 
 scalar_t__ ZFS_CASE_MIXED ; 
 TYPE_6__* ZTOZSB (TYPE_1__*) ; 
 int zap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zap_remove_norm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_dropname(zfs_dirlock_t *dl, znode_t *zp, znode_t *dzp, dmu_tx_t *tx,
    int flag)
{
	int error;

	if (ZTOZSB(zp)->z_norm) {
		matchtype_t mt = MT_NORMALIZE;

		if ((ZTOZSB(zp)->z_case == ZFS_CASE_INSENSITIVE &&
		    (flag & ZCIEXACT)) ||
		    (ZTOZSB(zp)->z_case == ZFS_CASE_MIXED &&
		    !(flag & ZCILOOK))) {
			mt |= MT_MATCH_CASE;
		}

		error = zap_remove_norm(ZTOZSB(zp)->z_os, dzp->z_id,
		    dl->dl_name, mt, tx);
	} else {
		error = zap_remove(ZTOZSB(zp)->z_os, dzp->z_id, dl->dl_name,
		    tx);
	}

	return (error);
}