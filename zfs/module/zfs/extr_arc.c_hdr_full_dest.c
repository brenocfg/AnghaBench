#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  b_arc_node; int /*<<< orphan*/  b_freeze_lock; int /*<<< orphan*/  b_refcnt; int /*<<< orphan*/  b_cv; } ;
struct TYPE_5__ {TYPE_1__ b_l1hdr; } ;
typedef  TYPE_2__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_SPACE_HDRS ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int HDR_EMPTY (TYPE_2__*) ; 
 int /*<<< orphan*/  HDR_FULL_SIZE ; 
 int /*<<< orphan*/  arc_space_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hdr_full_dest(void *vbuf, void *unused)
{
	arc_buf_hdr_t *hdr = vbuf;

	ASSERT(HDR_EMPTY(hdr));
	cv_destroy(&hdr->b_l1hdr.b_cv);
	zfs_refcount_destroy(&hdr->b_l1hdr.b_refcnt);
	mutex_destroy(&hdr->b_l1hdr.b_freeze_lock);
	ASSERT(!multilist_link_active(&hdr->b_l1hdr.b_arc_node));
	arc_space_return(HDR_FULL_SIZE, ARC_SPACE_HDRS);
}