#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {TYPE_1__* dn_phys; int /*<<< orphan*/  dn_struct_rwlock; } ;
typedef  TYPE_2__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dn_indblkshift; int /*<<< orphan*/  dn_datablkszsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int dbuf_findbp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dbuf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dbuf_dnode_findbp(dnode_t *dn, uint64_t level, uint64_t blkid,
    blkptr_t *bp, uint16_t *datablkszsec, uint8_t *indblkshift)
{
	dmu_buf_impl_t *dbp = NULL;
	blkptr_t *bp2;
	int err = 0;
	ASSERT(RW_LOCK_HELD(&dn->dn_struct_rwlock));

	err = dbuf_findbp(dn, level, blkid, B_FALSE, &dbp, &bp2);
	if (err == 0) {
		*bp = *bp2;
		if (dbp != NULL)
			dbuf_rele(dbp, NULL);
		if (datablkszsec != NULL)
			*datablkszsec = dn->dn_phys->dn_datablkszsec;
		if (indblkshift != NULL)
			*indblkshift = dn->dn_phys->dn_indblkshift;
	}

	return (err);
}