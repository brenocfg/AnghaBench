#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_7__ {int /*<<< orphan*/  vs_slow_ios; int /*<<< orphan*/ ** vsx_agg_histo; int /*<<< orphan*/ ** vsx_ind_histo; int /*<<< orphan*/ ** vsx_queue_histo; int /*<<< orphan*/ ** vsx_disk_histo; int /*<<< orphan*/ ** vsx_total_histo; int /*<<< orphan*/ * vsx_pend_queue; int /*<<< orphan*/ * vsx_active_queue; } ;
typedef  TYPE_1__ vdev_stat_t ;
typedef  TYPE_1__ vdev_stat_ex_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 size_t ZIO_PRIORITY_ASYNC_READ ; 
 size_t ZIO_PRIORITY_ASYNC_WRITE ; 
 size_t ZIO_PRIORITY_SCRUB ; 
 size_t ZIO_PRIORITY_SYNC_READ ; 
 size_t ZIO_PRIORITY_SYNC_WRITE ; 
 size_t ZIO_PRIORITY_TRIM ; 
 size_t ZIO_TYPE_READ ; 
 size_t ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_AGG_SCRUB_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_AGG_TRIM_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_AGG_R_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_AGG_W_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_IND_R_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_IND_W_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_R_ACTIVE_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_R_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_R_PEND_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_W_ACTIVE_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_W_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ASYNC_W_PEND_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_DISK_R_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_DISK_W_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_IND_SCRUB_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_IND_TRIM_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SCRUB_ACTIVE_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SCRUB_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SCRUB_PEND_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SLOW_IOS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS_EX ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_AGG_R_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_AGG_W_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_IND_R_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_IND_W_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_R_ACTIVE_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_R_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_R_PEND_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_W_ACTIVE_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_W_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_SYNC_W_PEND_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TOT_R_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TOT_W_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TRIM_ACTIVE_QUEUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TRIM_LAT_HISTO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TRIM_PEND_QUEUE ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vdev_get_stats_ex (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

void
vdev_config_generate_stats(vdev_t *vd, nvlist_t *nv)
{
	nvlist_t *nvx;
	vdev_stat_t *vs;
	vdev_stat_ex_t *vsx;

	vs = kmem_alloc(sizeof (*vs), KM_SLEEP);
	vsx = kmem_alloc(sizeof (*vsx), KM_SLEEP);

	vdev_get_stats_ex(vd, vs, vsx);
	fnvlist_add_uint64_array(nv, ZPOOL_CONFIG_VDEV_STATS,
	    (uint64_t *)vs, sizeof (*vs) / sizeof (uint64_t));

	/*
	 * Add extended stats into a special extended stats nvlist.  This keeps
	 * all the extended stats nicely grouped together.  The extended stats
	 * nvlist is then added to the main nvlist.
	 */
	nvx = fnvlist_alloc();

	/* ZIOs in flight to disk */
	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SYNC_R_ACTIVE_QUEUE,
	    vsx->vsx_active_queue[ZIO_PRIORITY_SYNC_READ]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SYNC_W_ACTIVE_QUEUE,
	    vsx->vsx_active_queue[ZIO_PRIORITY_SYNC_WRITE]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_ASYNC_R_ACTIVE_QUEUE,
	    vsx->vsx_active_queue[ZIO_PRIORITY_ASYNC_READ]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_ASYNC_W_ACTIVE_QUEUE,
	    vsx->vsx_active_queue[ZIO_PRIORITY_ASYNC_WRITE]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SCRUB_ACTIVE_QUEUE,
	    vsx->vsx_active_queue[ZIO_PRIORITY_SCRUB]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_TRIM_ACTIVE_QUEUE,
	    vsx->vsx_active_queue[ZIO_PRIORITY_TRIM]);

	/* ZIOs pending */
	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SYNC_R_PEND_QUEUE,
	    vsx->vsx_pend_queue[ZIO_PRIORITY_SYNC_READ]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SYNC_W_PEND_QUEUE,
	    vsx->vsx_pend_queue[ZIO_PRIORITY_SYNC_WRITE]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_ASYNC_R_PEND_QUEUE,
	    vsx->vsx_pend_queue[ZIO_PRIORITY_ASYNC_READ]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_ASYNC_W_PEND_QUEUE,
	    vsx->vsx_pend_queue[ZIO_PRIORITY_ASYNC_WRITE]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SCRUB_PEND_QUEUE,
	    vsx->vsx_pend_queue[ZIO_PRIORITY_SCRUB]);

	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_TRIM_PEND_QUEUE,
	    vsx->vsx_pend_queue[ZIO_PRIORITY_TRIM]);

	/* Histograms */
	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_TOT_R_LAT_HISTO,
	    vsx->vsx_total_histo[ZIO_TYPE_READ],
	    ARRAY_SIZE(vsx->vsx_total_histo[ZIO_TYPE_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_TOT_W_LAT_HISTO,
	    vsx->vsx_total_histo[ZIO_TYPE_WRITE],
	    ARRAY_SIZE(vsx->vsx_total_histo[ZIO_TYPE_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_DISK_R_LAT_HISTO,
	    vsx->vsx_disk_histo[ZIO_TYPE_READ],
	    ARRAY_SIZE(vsx->vsx_disk_histo[ZIO_TYPE_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_DISK_W_LAT_HISTO,
	    vsx->vsx_disk_histo[ZIO_TYPE_WRITE],
	    ARRAY_SIZE(vsx->vsx_disk_histo[ZIO_TYPE_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SYNC_R_LAT_HISTO,
	    vsx->vsx_queue_histo[ZIO_PRIORITY_SYNC_READ],
	    ARRAY_SIZE(vsx->vsx_queue_histo[ZIO_PRIORITY_SYNC_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SYNC_W_LAT_HISTO,
	    vsx->vsx_queue_histo[ZIO_PRIORITY_SYNC_WRITE],
	    ARRAY_SIZE(vsx->vsx_queue_histo[ZIO_PRIORITY_SYNC_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_ASYNC_R_LAT_HISTO,
	    vsx->vsx_queue_histo[ZIO_PRIORITY_ASYNC_READ],
	    ARRAY_SIZE(vsx->vsx_queue_histo[ZIO_PRIORITY_ASYNC_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_ASYNC_W_LAT_HISTO,
	    vsx->vsx_queue_histo[ZIO_PRIORITY_ASYNC_WRITE],
	    ARRAY_SIZE(vsx->vsx_queue_histo[ZIO_PRIORITY_ASYNC_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SCRUB_LAT_HISTO,
	    vsx->vsx_queue_histo[ZIO_PRIORITY_SCRUB],
	    ARRAY_SIZE(vsx->vsx_queue_histo[ZIO_PRIORITY_SCRUB]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_TRIM_LAT_HISTO,
	    vsx->vsx_queue_histo[ZIO_PRIORITY_TRIM],
	    ARRAY_SIZE(vsx->vsx_queue_histo[ZIO_PRIORITY_TRIM]));

	/* Request sizes */
	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SYNC_IND_R_HISTO,
	    vsx->vsx_ind_histo[ZIO_PRIORITY_SYNC_READ],
	    ARRAY_SIZE(vsx->vsx_ind_histo[ZIO_PRIORITY_SYNC_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SYNC_IND_W_HISTO,
	    vsx->vsx_ind_histo[ZIO_PRIORITY_SYNC_WRITE],
	    ARRAY_SIZE(vsx->vsx_ind_histo[ZIO_PRIORITY_SYNC_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_ASYNC_IND_R_HISTO,
	    vsx->vsx_ind_histo[ZIO_PRIORITY_ASYNC_READ],
	    ARRAY_SIZE(vsx->vsx_ind_histo[ZIO_PRIORITY_ASYNC_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_ASYNC_IND_W_HISTO,
	    vsx->vsx_ind_histo[ZIO_PRIORITY_ASYNC_WRITE],
	    ARRAY_SIZE(vsx->vsx_ind_histo[ZIO_PRIORITY_ASYNC_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_IND_SCRUB_HISTO,
	    vsx->vsx_ind_histo[ZIO_PRIORITY_SCRUB],
	    ARRAY_SIZE(vsx->vsx_ind_histo[ZIO_PRIORITY_SCRUB]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_IND_TRIM_HISTO,
	    vsx->vsx_ind_histo[ZIO_PRIORITY_TRIM],
	    ARRAY_SIZE(vsx->vsx_ind_histo[ZIO_PRIORITY_TRIM]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SYNC_AGG_R_HISTO,
	    vsx->vsx_agg_histo[ZIO_PRIORITY_SYNC_READ],
	    ARRAY_SIZE(vsx->vsx_agg_histo[ZIO_PRIORITY_SYNC_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_SYNC_AGG_W_HISTO,
	    vsx->vsx_agg_histo[ZIO_PRIORITY_SYNC_WRITE],
	    ARRAY_SIZE(vsx->vsx_agg_histo[ZIO_PRIORITY_SYNC_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_ASYNC_AGG_R_HISTO,
	    vsx->vsx_agg_histo[ZIO_PRIORITY_ASYNC_READ],
	    ARRAY_SIZE(vsx->vsx_agg_histo[ZIO_PRIORITY_ASYNC_READ]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_ASYNC_AGG_W_HISTO,
	    vsx->vsx_agg_histo[ZIO_PRIORITY_ASYNC_WRITE],
	    ARRAY_SIZE(vsx->vsx_agg_histo[ZIO_PRIORITY_ASYNC_WRITE]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_AGG_SCRUB_HISTO,
	    vsx->vsx_agg_histo[ZIO_PRIORITY_SCRUB],
	    ARRAY_SIZE(vsx->vsx_agg_histo[ZIO_PRIORITY_SCRUB]));

	fnvlist_add_uint64_array(nvx, ZPOOL_CONFIG_VDEV_AGG_TRIM_HISTO,
	    vsx->vsx_agg_histo[ZIO_PRIORITY_TRIM],
	    ARRAY_SIZE(vsx->vsx_agg_histo[ZIO_PRIORITY_TRIM]));

	/* IO delays */
	fnvlist_add_uint64(nvx, ZPOOL_CONFIG_VDEV_SLOW_IOS, vs->vs_slow_ios);

	/* Add extended stats nvlist to main nvlist */
	fnvlist_add_nvlist(nv, ZPOOL_CONFIG_VDEV_STATS_EX, nvx);

	fnvlist_free(nvx);
	kmem_free(vs, sizeof (*vs));
	kmem_free(vsx, sizeof (*vsx));
}