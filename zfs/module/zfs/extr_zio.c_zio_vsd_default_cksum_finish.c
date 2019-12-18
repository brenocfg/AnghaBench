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
struct TYPE_4__ {int /*<<< orphan*/  zcr_cbdata; } ;
typedef  TYPE_1__ zio_cksum_report_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  zfs_ereport_finish_checksum (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zio_vsd_default_cksum_finish(zio_cksum_report_t *zcr,
    const abd_t *good_buf)
{
	/* no processing needed */
	zfs_ereport_finish_checksum(zcr, good_buf, zcr->zcr_cbdata, B_FALSE);
}