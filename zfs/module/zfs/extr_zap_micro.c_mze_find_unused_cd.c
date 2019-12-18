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
struct TYPE_9__ {int /*<<< orphan*/  zap_avl; } ;
struct TYPE_10__ {int /*<<< orphan*/  zap_rwlock; int /*<<< orphan*/  zap_ismicro; TYPE_1__ zap_m; } ;
typedef  TYPE_2__ zap_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {scalar_t__ mze_hash; scalar_t__ mze_cd; } ;
typedef  TYPE_3__ mzap_ent_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_3__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
mze_find_unused_cd(zap_t *zap, uint64_t hash)
{
	mzap_ent_t mze_tofind;
	avl_index_t idx;
	avl_tree_t *avl = &zap->zap_m.zap_avl;

	ASSERT(zap->zap_ismicro);
	ASSERT(RW_LOCK_HELD(&zap->zap_rwlock));

	mze_tofind.mze_hash = hash;
	mze_tofind.mze_cd = 0;

	uint32_t cd = 0;
	for (mzap_ent_t *mze = avl_find(avl, &mze_tofind, &idx);
	    mze && mze->mze_hash == hash; mze = AVL_NEXT(avl, mze)) {
		if (mze->mze_cd != cd)
			break;
		cd++;
	}

	return (cd);
}