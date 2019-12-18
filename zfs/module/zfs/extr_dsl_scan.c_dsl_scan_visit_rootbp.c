#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  zb_objset; } ;
typedef  TYPE_2__ zbookmark_phys_t ;
typedef  int /*<<< orphan*/  scan_prefetch_ctx_t ;
struct TYPE_15__ {TYPE_2__ scn_bookmark; } ;
struct TYPE_17__ {int /*<<< orphan*/  scn_objsets_visited_this_txg; TYPE_1__ scn_phys; TYPE_2__ scn_prefetch_bookmark; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_18__ {int /*<<< orphan*/  ds_object; } ;
typedef  TYPE_4__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_META_OBJSET ; 
 int /*<<< orphan*/  DMU_OST_NONE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SET_BOOKMARK (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZB_IS_ZERO (TYPE_2__*) ; 
 int /*<<< orphan*/  ZB_ROOT_BLKID ; 
 int /*<<< orphan*/  ZB_ROOT_LEVEL ; 
 int /*<<< orphan*/  ZB_ROOT_OBJECT ; 
 int /*<<< orphan*/  dprintf_ds (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  dsl_scan_prefetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_scan_visitbp (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scan_prefetch_ctx_create (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_prefetch_ctx_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_scan_visit_rootbp(dsl_scan_t *scn, dsl_dataset_t *ds, blkptr_t *bp,
    dmu_tx_t *tx)
{
	zbookmark_phys_t zb;
	scan_prefetch_ctx_t *spc;

	SET_BOOKMARK(&zb, ds ? ds->ds_object : DMU_META_OBJSET,
	    ZB_ROOT_OBJECT, ZB_ROOT_LEVEL, ZB_ROOT_BLKID);

	if (ZB_IS_ZERO(&scn->scn_phys.scn_bookmark)) {
		SET_BOOKMARK(&scn->scn_prefetch_bookmark,
		    zb.zb_objset, 0, 0, 0);
	} else {
		scn->scn_prefetch_bookmark = scn->scn_phys.scn_bookmark;
	}

	scn->scn_objsets_visited_this_txg++;

	spc = scan_prefetch_ctx_create(scn, NULL, FTAG);
	dsl_scan_prefetch(spc, bp, &zb);
	scan_prefetch_ctx_rele(spc, FTAG);

	dsl_scan_visitbp(bp, &zb, NULL, ds, scn, DMU_OST_NONE, tx);

	dprintf_ds(ds, "finished scan%s", "");
}