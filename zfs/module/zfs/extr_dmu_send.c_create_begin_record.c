#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct drr_begin {int /*<<< orphan*/  drr_toname; int /*<<< orphan*/  drr_flags; int /*<<< orphan*/  drr_versioninfo; int /*<<< orphan*/  drr_fromguid; int /*<<< orphan*/  drr_toguid; int /*<<< orphan*/  drr_type; int /*<<< orphan*/  drr_creation_time; int /*<<< orphan*/  drr_magic; } ;
struct TYPE_10__ {int /*<<< orphan*/  zbm_guid; } ;
struct dmu_send_params {TYPE_3__* to_ds; scalar_t__ is_clone; TYPE_1__ ancestor_zb; } ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_12__ {int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_11__ {struct drr_begin drr_begin; } ;
struct TYPE_13__ {TYPE_2__ drr_u; int /*<<< orphan*/  drr_type; } ;
typedef  TYPE_4__ dmu_replay_record_t ;
struct TYPE_14__ {int ds_flags; int /*<<< orphan*/  ds_guid; int /*<<< orphan*/  ds_creation_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_BACKUP_MAGIC ; 
 int /*<<< orphan*/  DMU_SET_FEATUREFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_SET_STREAM_HDRTYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_SUBSTREAM ; 
 int /*<<< orphan*/  DRR_BEGIN ; 
 int /*<<< orphan*/  DRR_FLAG_CI_DATA ; 
 int /*<<< orphan*/  DRR_FLAG_CLONE ; 
 int /*<<< orphan*/  DRR_FLAG_FREERECORDS ; 
 int /*<<< orphan*/  DRR_FLAG_SPILL_BLOCK ; 
 int DS_FLAG_CI_DATASET ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  dmu_objset_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* dsl_dataset_phys (TYPE_3__*) ; 
 TYPE_4__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zfs_send_set_freerecords_bit ; 

__attribute__((used)) static dmu_replay_record_t *
create_begin_record(struct dmu_send_params *dspp, objset_t *os,
    uint64_t featureflags)
{
	dmu_replay_record_t *drr = kmem_zalloc(sizeof (dmu_replay_record_t),
	    KM_SLEEP);
	drr->drr_type = DRR_BEGIN;

	struct drr_begin *drrb = &drr->drr_u.drr_begin;
	dsl_dataset_t *to_ds = dspp->to_ds;

	drrb->drr_magic = DMU_BACKUP_MAGIC;
	drrb->drr_creation_time = dsl_dataset_phys(to_ds)->ds_creation_time;
	drrb->drr_type = dmu_objset_type(os);
	drrb->drr_toguid = dsl_dataset_phys(to_ds)->ds_guid;
	drrb->drr_fromguid = dspp->ancestor_zb.zbm_guid;

	DMU_SET_STREAM_HDRTYPE(drrb->drr_versioninfo, DMU_SUBSTREAM);
	DMU_SET_FEATUREFLAGS(drrb->drr_versioninfo, featureflags);

	if (dspp->is_clone)
		drrb->drr_flags |= DRR_FLAG_CLONE;
	if (dsl_dataset_phys(dspp->to_ds)->ds_flags & DS_FLAG_CI_DATASET)
		drrb->drr_flags |= DRR_FLAG_CI_DATA;
	if (zfs_send_set_freerecords_bit)
		drrb->drr_flags |= DRR_FLAG_FREERECORDS;
	drr->drr_u.drr_begin.drr_flags |= DRR_FLAG_SPILL_BLOCK;

	dsl_dataset_name(to_ds, drrb->drr_toname);
	if (!to_ds->ds_is_snapshot) {
		(void) strlcat(drrb->drr_toname, "@--head--",
		    sizeof (drrb->drr_toname));
	}
	return (drr);
}