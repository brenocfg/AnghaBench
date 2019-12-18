#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct stat_array {int /*<<< orphan*/  count; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  cb_scripted; scalar_t__ cb_literal; } ;
typedef  TYPE_1__ iostat_cbdata_t ;
typedef  enum zfs_nicenum_format { ____Placeholder_zfs_nicenum_format } zfs_nicenum_format ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  IOS_LATENCY ; 
 int ZFS_NICENUM_RAWTIME ; 
 int ZFS_NICENUM_TIME ; 
 char const* ZPOOL_CONFIG_VDEV_ASYNC_R_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_ASYNC_W_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_DISK_R_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_DISK_W_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_SCRUB_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_SYNC_R_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_SYNC_W_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_TOT_R_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_TOT_W_LAT_HISTO ; 
 char const* ZPOOL_CONFIG_VDEV_TRIM_LAT_HISTO ; 
 struct stat_array* calc_and_alloc_stats_ex (char const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int default_column_width (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_calc_stats (struct stat_array*,int) ; 
 int /*<<< orphan*/  print_one_stat (int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_histo_average (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_iostat_latency(iostat_cbdata_t *cb, nvlist_t *oldnv,
    nvlist_t *newnv)
{
	int i;
	uint64_t val;
	const char *names[] = {
		ZPOOL_CONFIG_VDEV_TOT_R_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_TOT_W_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_DISK_R_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_DISK_W_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_SYNC_R_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_SYNC_W_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_ASYNC_R_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_ASYNC_W_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_SCRUB_LAT_HISTO,
		ZPOOL_CONFIG_VDEV_TRIM_LAT_HISTO,
	};
	struct stat_array *nva;

	unsigned int column_width = default_column_width(cb, IOS_LATENCY);
	enum zfs_nicenum_format format;

	nva = calc_and_alloc_stats_ex(names, ARRAY_SIZE(names), oldnv, newnv);

	if (cb->cb_literal)
		format = ZFS_NICENUM_RAWTIME;
	else
		format = ZFS_NICENUM_TIME;

	/* Print our avg latencies on the line */
	for (i = 0; i < ARRAY_SIZE(names); i++) {
		/* Compute average latency for a latency histo */
		val = single_histo_average(nva[i].data, nva[i].count);
		print_one_stat(val, format, column_width, cb->cb_scripted);
	}
	free_calc_stats(nva, ARRAY_SIZE(names));
}