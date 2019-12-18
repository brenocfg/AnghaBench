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
struct TYPE_3__ {int /*<<< orphan*/ * zcr_detector; int /*<<< orphan*/  zcr_ereport; int /*<<< orphan*/  zcr_length; int /*<<< orphan*/  zcr_ckinfo; } ;
typedef  TYPE_1__ zio_cksum_report_t ;
typedef  int /*<<< orphan*/  zfs_ecksum_info_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/ * annotate_ecksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_zevent_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  zfs_zevent_post_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
zfs_ereport_finish_checksum(zio_cksum_report_t *report, const abd_t *good_data,
    const abd_t *bad_data, boolean_t drop_if_identical)
{
#ifdef _KERNEL
	zfs_ecksum_info_t *info;

	info = annotate_ecksum(report->zcr_ereport, report->zcr_ckinfo,
	    good_data, bad_data, report->zcr_length, drop_if_identical);
	if (info != NULL)
		zfs_zevent_post(report->zcr_ereport,
		    report->zcr_detector, zfs_zevent_post_cb);
	else
		zfs_zevent_post_cb(report->zcr_ereport, report->zcr_detector);

	report->zcr_ereport = report->zcr_detector = NULL;
	if (info != NULL)
		kmem_free(info, sizeof (*info));
#endif
}