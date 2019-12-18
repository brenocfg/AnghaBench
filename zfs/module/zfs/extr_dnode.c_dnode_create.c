#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_14__ {int /*<<< orphan*/  os_lock; int /*<<< orphan*/  os_dnodes; } ;
typedef  TYPE_1__ objset_t ;
struct TYPE_15__ {int dn_have_spill; TYPE_1__* dn_objset; TYPE_3__* dn_phys; int /*<<< orphan*/  dn_zfetch; scalar_t__ dn_id_flags; int /*<<< orphan*/  dn_maxblkid; scalar_t__ dn_num_slots; int /*<<< orphan*/  dn_bonuslen; int /*<<< orphan*/  dn_bonustype; int /*<<< orphan*/  dn_compress; int /*<<< orphan*/  dn_checksum; int /*<<< orphan*/  dn_nblkptr; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_nlevels; int /*<<< orphan*/  dn_indblkshift; scalar_t__ dn_datablkshift; scalar_t__ dn_datablkszsec; scalar_t__ dn_datablksz; TYPE_4__* dn_handle; int /*<<< orphan*/ * dn_dbuf; int /*<<< orphan*/  dn_object; scalar_t__ dn_moved; } ;
typedef  TYPE_2__ dnode_t ;
struct TYPE_16__ {int dn_datablkszsec; int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_maxblkid; scalar_t__ dn_extra_slots; int /*<<< orphan*/  dn_bonuslen; int /*<<< orphan*/  dn_bonustype; int /*<<< orphan*/  dn_compress; int /*<<< orphan*/  dn_checksum; int /*<<< orphan*/  dn_nblkptr; int /*<<< orphan*/  dn_nlevels; int /*<<< orphan*/  dn_indblkshift; } ;
typedef  TYPE_3__ dnode_phys_t ;
struct TYPE_17__ {TYPE_2__* dnh_dnode; int /*<<< orphan*/  dnh_zrlock; } ;
typedef  TYPE_4__ dnode_handle_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_SPACE_DNODE ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_OBJECT_IS_SPECIAL (int /*<<< orphan*/ ) ; 
 int DMU_OT_IS_VALID (int /*<<< orphan*/ ) ; 
 int DNODE_FLAG_SPILL_BLKPTR ; 
 int /*<<< orphan*/  DN_SLOT_IS_PTR (TYPE_2__*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  arc_space_consume (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_zfetch_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dnode_cache ; 
 int /*<<< orphan*/  dnode_setdblksz (TYPE_2__*,int) ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  membar_producer () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int zrl_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dnode_t *
dnode_create(objset_t *os, dnode_phys_t *dnp, dmu_buf_impl_t *db,
    uint64_t object, dnode_handle_t *dnh)
{
	dnode_t *dn;

	dn = kmem_cache_alloc(dnode_cache, KM_SLEEP);
	dn->dn_moved = 0;

	/*
	 * Defer setting dn_objset until the dnode is ready to be a candidate
	 * for the dnode_move() callback.
	 */
	dn->dn_object = object;
	dn->dn_dbuf = db;
	dn->dn_handle = dnh;
	dn->dn_phys = dnp;

	if (dnp->dn_datablkszsec) {
		dnode_setdblksz(dn, dnp->dn_datablkszsec << SPA_MINBLOCKSHIFT);
	} else {
		dn->dn_datablksz = 0;
		dn->dn_datablkszsec = 0;
		dn->dn_datablkshift = 0;
	}
	dn->dn_indblkshift = dnp->dn_indblkshift;
	dn->dn_nlevels = dnp->dn_nlevels;
	dn->dn_type = dnp->dn_type;
	dn->dn_nblkptr = dnp->dn_nblkptr;
	dn->dn_checksum = dnp->dn_checksum;
	dn->dn_compress = dnp->dn_compress;
	dn->dn_bonustype = dnp->dn_bonustype;
	dn->dn_bonuslen = dnp->dn_bonuslen;
	dn->dn_num_slots = dnp->dn_extra_slots + 1;
	dn->dn_maxblkid = dnp->dn_maxblkid;
	dn->dn_have_spill = ((dnp->dn_flags & DNODE_FLAG_SPILL_BLKPTR) != 0);
	dn->dn_id_flags = 0;

	dmu_zfetch_init(&dn->dn_zfetch, dn);

	ASSERT(DMU_OT_IS_VALID(dn->dn_phys->dn_type));
	ASSERT(zrl_is_locked(&dnh->dnh_zrlock));
	ASSERT(!DN_SLOT_IS_PTR(dnh->dnh_dnode));

	mutex_enter(&os->os_lock);

	/*
	 * Exclude special dnodes from os_dnodes so an empty os_dnodes
	 * signifies that the special dnodes have no references from
	 * their children (the entries in os_dnodes).  This allows
	 * dnode_destroy() to easily determine if the last child has
	 * been removed and then complete eviction of the objset.
	 */
	if (!DMU_OBJECT_IS_SPECIAL(object))
		list_insert_head(&os->os_dnodes, dn);
	membar_producer();

	/*
	 * Everything else must be valid before assigning dn_objset
	 * makes the dnode eligible for dnode_move().
	 */
	dn->dn_objset = os;

	dnh->dnh_dnode = dn;
	mutex_exit(&os->os_lock);

	arc_space_consume(sizeof (dnode_t), ARC_SPACE_DNODE);

	return (dn);
}