#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zap_object; int /*<<< orphan*/  zap_objset; } ;
typedef  TYPE_2__ zap_t ;
struct TYPE_11__ {int /*<<< orphan*/  zn_hash; TYPE_2__* zn_zap; } ;
typedef  TYPE_3__ zap_name_t ;
typedef  int uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  zt_shift; } ;
struct TYPE_12__ {TYPE_1__ zap_ptrtbl; } ;

/* Variables and functions */
 int FZAP_BLOCK_SHIFT (TYPE_2__*) ; 
 int ZAP_HASH_IDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/  dmu_prefetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* zap_f_phys (TYPE_2__*) ; 
 scalar_t__ zap_idx_to_blk (TYPE_2__*,int,int*) ; 

void
fzap_prefetch(zap_name_t *zn)
{
	uint64_t blk;
	zap_t *zap = zn->zn_zap;

	uint64_t idx = ZAP_HASH_IDX(zn->zn_hash,
	    zap_f_phys(zap)->zap_ptrtbl.zt_shift);
	if (zap_idx_to_blk(zap, idx, &blk) != 0)
		return;
	int bs = FZAP_BLOCK_SHIFT(zap);
	dmu_prefetch(zap->zap_objset, zap->zap_object, 0, blk << bs, 1 << bs,
	    ZIO_PRIORITY_SYNC_READ);
}