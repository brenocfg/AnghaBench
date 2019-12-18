#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vdev_alloc_bias; scalar_t__ vdev_top_zap; scalar_t__ vdev_ms_count; scalar_t__ vdev_id; int /*<<< orphan*/  vdev_spa; scalar_t__ vdev_islog; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ vdev_alloc_bias_t ;
typedef  scalar_t__ uint64_t ;
typedef  char* u_longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int ENOENT ; 
 char* VDEV_ALLOC_BIAS_DEDUP ; 
 char* VDEV_ALLOC_BIAS_LOG ; 
 char* VDEV_ALLOC_BIAS_SPECIAL ; 
 scalar_t__ VDEV_BIAS_DEDUP ; 
 scalar_t__ VDEV_BIAS_LOG ; 
 scalar_t__ VDEV_BIAS_SPECIAL ; 
 int /*<<< orphan*/  VDEV_TOP_ZAP_MS_UNFLUSHED_PHYS_TXGS ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  spa_meta_objset (int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static void
print_vdev_metaslab_header(vdev_t *vd)
{
	vdev_alloc_bias_t alloc_bias = vd->vdev_alloc_bias;
	const char *bias_str = "";
	if (alloc_bias == VDEV_BIAS_LOG || vd->vdev_islog) {
		bias_str = VDEV_ALLOC_BIAS_LOG;
	} else if (alloc_bias == VDEV_BIAS_SPECIAL) {
		bias_str = VDEV_ALLOC_BIAS_SPECIAL;
	} else if (alloc_bias == VDEV_BIAS_DEDUP) {
		bias_str = VDEV_ALLOC_BIAS_DEDUP;
	}

	uint64_t ms_flush_data_obj = 0;
	if (vd->vdev_top_zap != 0) {
		int error = zap_lookup(spa_meta_objset(vd->vdev_spa),
		    vd->vdev_top_zap, VDEV_TOP_ZAP_MS_UNFLUSHED_PHYS_TXGS,
		    sizeof (uint64_t), 1, &ms_flush_data_obj);
		if (error != ENOENT) {
			ASSERT0(error);
		}
	}

	(void) printf("\tvdev %10llu   %s",
	    (u_longlong_t)vd->vdev_id, bias_str);

	if (ms_flush_data_obj != 0) {
		(void) printf("   ms_unflushed_phys object %llu",
		    (u_longlong_t)ms_flush_data_obj);
	}

	(void) printf("\n\t%-10s%5llu   %-19s   %-15s   %-12s\n",
	    "metaslabs", (u_longlong_t)vd->vdev_ms_count,
	    "offset", "spacemap", "free");
	(void) printf("\t%15s   %19s   %15s   %12s\n",
	    "---------------", "-------------------",
	    "---------------", "------------");
}