#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  b_hdr; } ;
typedef  TYPE_1__ arc_buf_t ;

/* Variables and functions */
 scalar_t__ ARC_BUF_COMPRESSED (TYPE_1__*) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDR_HAS_L1HDR (int /*<<< orphan*/ ) ; 
 int ZFS_DEBUG_MODIFY ; 
 int /*<<< orphan*/  arc_cksum_compute (TYPE_1__*) ; 
 int zfs_flags ; 

void
arc_buf_freeze(arc_buf_t *buf)
{
	if (!(zfs_flags & ZFS_DEBUG_MODIFY))
		return;

	if (ARC_BUF_COMPRESSED(buf))
		return;

	ASSERT(HDR_HAS_L1HDR(buf->b_hdr));
	arc_cksum_compute(buf);
}