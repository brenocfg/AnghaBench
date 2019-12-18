#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  zap_object; int /*<<< orphan*/ * zap_objset; } ;
typedef  TYPE_3__ zap_t ;
struct TYPE_17__ {TYPE_3__* zn_zap; } ;
typedef  TYPE_4__ zap_name_t ;
typedef  int /*<<< orphan*/  zap_leaf_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_14__ {int lh_prefix_len; scalar_t__ lh_nfree; } ;
struct TYPE_18__ {TYPE_1__ l_hdr; } ;
struct TYPE_15__ {int zt_shift; scalar_t__ zt_nextblk; } ;
struct TYPE_13__ {TYPE_2__ zap_ptrtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ ZAP_LEAF_LOW_WATER ; 
 TYPE_11__* zap_f_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  zap_grow_ptrtbl (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_9__* zap_leaf_phys (int /*<<< orphan*/ *) ; 
 int zap_lockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_3__**) ; 
 int /*<<< orphan*/  zap_put_leaf (int /*<<< orphan*/ *) ; 
 scalar_t__ zap_tryupgradedir (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_unlockdir (TYPE_3__*,void*) ; 

__attribute__((used)) static void
zap_put_leaf_maybe_grow_ptrtbl(zap_name_t *zn, zap_leaf_t *l,
    void *tag, dmu_tx_t *tx)
{
	zap_t *zap = zn->zn_zap;
	int shift = zap_f_phys(zap)->zap_ptrtbl.zt_shift;
	int leaffull = (zap_leaf_phys(l)->l_hdr.lh_prefix_len == shift &&
	    zap_leaf_phys(l)->l_hdr.lh_nfree < ZAP_LEAF_LOW_WATER);

	zap_put_leaf(l);

	if (leaffull || zap_f_phys(zap)->zap_ptrtbl.zt_nextblk) {
		/*
		 * We are in the middle of growing the pointer table, or
		 * this leaf will soon make us grow it.
		 */
		if (zap_tryupgradedir(zap, tx) == 0) {
			objset_t *os = zap->zap_objset;
			uint64_t zapobj = zap->zap_object;

			zap_unlockdir(zap, tag);
			int err = zap_lockdir(os, zapobj, tx,
			    RW_WRITER, FALSE, FALSE, tag, &zn->zn_zap);
			zap = zn->zn_zap;
			if (err != 0)
				return;
		}

		/* could have finished growing while our locks were down */
		if (zap_f_phys(zap)->zap_ptrtbl.zt_shift == shift)
			(void) zap_grow_ptrtbl(zap, tx);
	}
}