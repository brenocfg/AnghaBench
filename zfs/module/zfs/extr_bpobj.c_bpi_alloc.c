#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {TYPE_1__* bpo_phys; scalar_t__ bpo_havesubobj; } ;
typedef  TYPE_2__ bpobj_t ;
struct TYPE_10__ {int /*<<< orphan*/  bpi_unprocessed_subobjs; int /*<<< orphan*/  bpi_index; struct TYPE_10__* bpi_parent; TYPE_2__* bpi_bpo; } ;
typedef  TYPE_3__ bpobj_info_t ;
struct TYPE_8__ {scalar_t__ bpo_subobjs; int /*<<< orphan*/  bpo_num_subobjs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_3__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bpobj_info_t *
bpi_alloc(bpobj_t *bpo, bpobj_info_t *parent, uint64_t index)
{
	bpobj_info_t *bpi = kmem_zalloc(sizeof (bpobj_info_t), KM_SLEEP);
	bpi->bpi_bpo = bpo;
	bpi->bpi_parent = parent;
	bpi->bpi_index = index;
	if (bpo->bpo_havesubobj && bpo->bpo_phys->bpo_subobjs != 0) {
		bpi->bpi_unprocessed_subobjs = bpo->bpo_phys->bpo_num_subobjs;
	}
	return (bpi);
}