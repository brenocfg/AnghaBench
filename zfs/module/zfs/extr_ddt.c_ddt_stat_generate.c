#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_10__ {int /*<<< orphan*/ * ddt_spa; } ;
typedef  TYPE_1__ ddt_t ;
struct TYPE_11__ {int dds_blocks; int dds_lsize; int dds_psize; int dds_dsize; int dds_ref_blocks; int dds_ref_lsize; int dds_ref_psize; int dds_ref_dsize; } ;
typedef  TYPE_2__ ddt_stat_t ;
struct TYPE_12__ {int ddp_refcnt; scalar_t__ ddp_phys_birth; int /*<<< orphan*/ * ddp_dva; } ;
typedef  TYPE_3__ ddt_phys_t ;
typedef  int /*<<< orphan*/  ddt_key_t ;
struct TYPE_13__ {int /*<<< orphan*/  dde_key; TYPE_3__* dde_phys; } ;
typedef  TYPE_4__ ddt_entry_t ;

/* Variables and functions */
 int DDE_GET_NDVAS (TYPE_4__*) ; 
 int DDK_GET_LSIZE (int /*<<< orphan*/ *) ; 
 int DDK_GET_PSIZE (int /*<<< orphan*/ *) ; 
 int DDT_PHYS_TYPES ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 scalar_t__ dva_get_dsize_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ddt_stat_generate(ddt_t *ddt, ddt_entry_t *dde, ddt_stat_t *dds)
{
	spa_t *spa = ddt->ddt_spa;
	ddt_phys_t *ddp = dde->dde_phys;
	ddt_key_t *ddk = &dde->dde_key;
	uint64_t lsize = DDK_GET_LSIZE(ddk);
	uint64_t psize = DDK_GET_PSIZE(ddk);

	bzero(dds, sizeof (*dds));

	for (int p = 0; p < DDT_PHYS_TYPES; p++, ddp++) {
		uint64_t dsize = 0;
		uint64_t refcnt = ddp->ddp_refcnt;

		if (ddp->ddp_phys_birth == 0)
			continue;

		for (int d = 0; d < DDE_GET_NDVAS(dde); d++)
			dsize += dva_get_dsize_sync(spa, &ddp->ddp_dva[d]);

		dds->dds_blocks += 1;
		dds->dds_lsize += lsize;
		dds->dds_psize += psize;
		dds->dds_dsize += dsize;

		dds->dds_ref_blocks += refcnt;
		dds->dds_ref_lsize += lsize * refcnt;
		dds->dds_ref_psize += psize * refcnt;
		dds->dds_ref_dsize += dsize * refcnt;
	}
}