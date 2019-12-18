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
struct TYPE_8__ {int zb_blkid; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
struct TYPE_9__ {int /*<<< orphan*/  dn_objset; int /*<<< orphan*/  dn_object; TYPE_3__* dn_phys; } ;
typedef  TYPE_2__ dnode_t ;
struct TYPE_10__ {int dn_nblkptr; int /*<<< orphan*/ * dn_blkptr; scalar_t__ dn_nlevels; } ;
typedef  TYPE_3__ dnode_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BOOKMARK (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  visit_indirect (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
dump_indirect(dnode_t *dn)
{
	dnode_phys_t *dnp = dn->dn_phys;
	int j;
	zbookmark_phys_t czb;

	(void) printf("Indirect blocks:\n");

	SET_BOOKMARK(&czb, dmu_objset_id(dn->dn_objset),
	    dn->dn_object, dnp->dn_nlevels - 1, 0);
	for (j = 0; j < dnp->dn_nblkptr; j++) {
		czb.zb_blkid = j;
		(void) visit_indirect(dmu_objset_spa(dn->dn_objset), dnp,
		    &dnp->dn_blkptr[j], &czb);
	}

	(void) printf("\n");
}