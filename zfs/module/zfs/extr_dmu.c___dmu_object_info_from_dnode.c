#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dn_datablksz; int dn_indblkshift; int dn_num_slots; int dn_maxblkid; int /*<<< orphan*/  dn_nblkptr; int /*<<< orphan*/  dn_compress; int /*<<< orphan*/  dn_checksum; int /*<<< orphan*/  dn_nlevels; int /*<<< orphan*/  dn_bonuslen; int /*<<< orphan*/  dn_bonustype; int /*<<< orphan*/  dn_type; TYPE_2__* dn_phys; } ;
typedef  TYPE_1__ dnode_t ;
struct TYPE_8__ {int dn_nblkptr; int /*<<< orphan*/ * dn_blkptr; } ;
typedef  TYPE_2__ dnode_phys_t ;
struct TYPE_9__ {int doi_data_block_size; unsigned long long doi_metadata_block_size; int doi_dnodesize; int doi_physical_blocks_512; int doi_max_offset; scalar_t__ doi_fill_count; int /*<<< orphan*/  doi_nblkptr; int /*<<< orphan*/  doi_compress; int /*<<< orphan*/  doi_checksum; int /*<<< orphan*/  doi_indirection; int /*<<< orphan*/  doi_bonus_size; int /*<<< orphan*/  doi_bonus_type; int /*<<< orphan*/  doi_type; } ;
typedef  TYPE_3__ dmu_object_info_t ;

/* Variables and functions */
 scalar_t__ BP_GET_FILL (int /*<<< orphan*/ *) ; 
 int DNODE_SHIFT ; 
 int DN_USED_BYTES (TYPE_2__*) ; 

void
__dmu_object_info_from_dnode(dnode_t *dn, dmu_object_info_t *doi)
{
	dnode_phys_t *dnp = dn->dn_phys;

	doi->doi_data_block_size = dn->dn_datablksz;
	doi->doi_metadata_block_size = dn->dn_indblkshift ?
	    1ULL << dn->dn_indblkshift : 0;
	doi->doi_type = dn->dn_type;
	doi->doi_bonus_type = dn->dn_bonustype;
	doi->doi_bonus_size = dn->dn_bonuslen;
	doi->doi_dnodesize = dn->dn_num_slots << DNODE_SHIFT;
	doi->doi_indirection = dn->dn_nlevels;
	doi->doi_checksum = dn->dn_checksum;
	doi->doi_compress = dn->dn_compress;
	doi->doi_nblkptr = dn->dn_nblkptr;
	doi->doi_physical_blocks_512 = (DN_USED_BYTES(dnp) + 256) >> 9;
	doi->doi_max_offset = (dn->dn_maxblkid + 1) * dn->dn_datablksz;
	doi->doi_fill_count = 0;
	for (int i = 0; i < dnp->dn_nblkptr; i++)
		doi->doi_fill_count += BP_GET_FILL(&dnp->dn_blkptr[i]);
}