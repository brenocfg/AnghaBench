#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ z_size; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_10__ {int /*<<< orphan*/  z_log; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_11__ {scalar_t__ lr_offset; scalar_t__ lr_length; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_3__ lr_write_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ERESTART ; 
 int /*<<< orphan*/  SA_ZPL_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZTOI (TYPE_1__*) ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int zfs_zget (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  zil_replaying (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_replay_write2(void *arg1, void *arg2, boolean_t byteswap)
{
	zfsvfs_t *zfsvfs = arg1;
	lr_write_t *lr = arg2;
	znode_t	*zp;
	int error;
	uint64_t end;

	if (byteswap)
		byteswap_uint64_array(lr, sizeof (*lr));

	if ((error = zfs_zget(zfsvfs, lr->lr_foid, &zp)) != 0)
		return (error);

top:
	end = lr->lr_offset + lr->lr_length;
	if (end > zp->z_size) {
		dmu_tx_t *tx = dmu_tx_create(zfsvfs->z_os);

		zp->z_size = end;
		dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_FALSE);
		error = dmu_tx_assign(tx, TXG_WAIT);
		if (error) {
			iput(ZTOI(zp));
			if (error == ERESTART) {
				dmu_tx_wait(tx);
				dmu_tx_abort(tx);
				goto top;
			}
			dmu_tx_abort(tx);
			return (error);
		}
		(void) sa_update(zp->z_sa_hdl, SA_ZPL_SIZE(zfsvfs),
		    (void *)&zp->z_size, sizeof (uint64_t), tx);

		/* Ensure the replayed seq is updated */
		(void) zil_replaying(zfsvfs->z_log, tx);

		dmu_tx_commit(tx);
	}

	iput(ZTOI(zp));

	return (error);
}