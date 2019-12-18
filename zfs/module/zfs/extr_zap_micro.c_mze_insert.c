#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zap_avl; } ;
struct TYPE_11__ {int zap_ismicro; TYPE_1__ zap_m; int /*<<< orphan*/  zap_rwlock; } ;
typedef  TYPE_2__ zap_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_12__ {int mze_chunkid; int /*<<< orphan*/  mze_cd; int /*<<< orphan*/  mze_hash; } ;
typedef  TYPE_3__ mzap_ent_t ;
struct TYPE_13__ {scalar_t__* mze_name; int /*<<< orphan*/  mze_cd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_7__* MZE_PHYS (TYPE_2__*,TYPE_3__*) ; 
 int RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* kmem_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mze_insert(zap_t *zap, int chunkid, uint64_t hash)
{
	ASSERT(zap->zap_ismicro);
	ASSERT(RW_WRITE_HELD(&zap->zap_rwlock));

	mzap_ent_t *mze = kmem_alloc(sizeof (mzap_ent_t), KM_SLEEP);
	mze->mze_chunkid = chunkid;
	mze->mze_hash = hash;
	mze->mze_cd = MZE_PHYS(zap, mze)->mze_cd;
	ASSERT(MZE_PHYS(zap, mze)->mze_name[0] != 0);
	avl_add(&zap->zap_m.zap_avl, mze);
}