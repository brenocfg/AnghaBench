#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zil_header_t ;
struct TYPE_2__ {int /*<<< orphan*/  os_projectused_dnode; int /*<<< orphan*/  os_groupused_dnode; int /*<<< orphan*/  os_userused_dnode; void* os_flags; void* os_type; int /*<<< orphan*/  os_zil_header; int /*<<< orphan*/  os_meta_dnode; } ;
typedef  TYPE_1__ objset_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* BSWAP_64 (void*) ; 
 size_t OBJSET_PHYS_SIZE_V1 ; 
 size_t OBJSET_PHYS_SIZE_V2 ; 
 int /*<<< orphan*/  byteswap_uint64_array (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dnode_byteswap (int /*<<< orphan*/ *) ; 

void
dmu_objset_byteswap(void *buf, size_t size)
{
	objset_phys_t *osp = buf;

	ASSERT(size == OBJSET_PHYS_SIZE_V1 || size == OBJSET_PHYS_SIZE_V2 ||
	    size == sizeof (objset_phys_t));
	dnode_byteswap(&osp->os_meta_dnode);
	byteswap_uint64_array(&osp->os_zil_header, sizeof (zil_header_t));
	osp->os_type = BSWAP_64(osp->os_type);
	osp->os_flags = BSWAP_64(osp->os_flags);
	if (size >= OBJSET_PHYS_SIZE_V2) {
		dnode_byteswap(&osp->os_userused_dnode);
		dnode_byteswap(&osp->os_groupused_dnode);
		if (size >= sizeof (objset_phys_t))
			dnode_byteswap(&osp->os_projectused_dnode);
	}
}