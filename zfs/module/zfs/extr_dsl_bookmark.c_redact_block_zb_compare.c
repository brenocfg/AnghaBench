#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zb_object; int zb_blkid; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
struct TYPE_7__ {scalar_t__ rbp_object; int rbp_blkid; } ;
typedef  TYPE_2__ redact_block_phys_t ;

/* Variables and functions */
 int redact_block_get_count (TYPE_2__*) ; 

__attribute__((used)) static int
redact_block_zb_compare(redact_block_phys_t *first,
    zbookmark_phys_t *second)
{
	/*
	 * If the block_phys is for a previous object, or the last block in the
	 * block_phys is strictly before the block in the bookmark, the
	 * block_phys is earlier.
	 */
	if (first->rbp_object < second->zb_object ||
	    (first->rbp_object == second->zb_object &&
	    first->rbp_blkid + (redact_block_get_count(first) - 1) <
	    second->zb_blkid)) {
		return (-1);
	}

	/*
	 * If the bookmark is for a previous object, or the block in the
	 * bookmark is strictly before the first block in the block_phys, the
	 * bookmark is earlier.
	 */
	if (first->rbp_object > second->zb_object ||
	    (first->rbp_object == second->zb_object &&
	    first->rbp_blkid > second->zb_blkid)) {
		return (1);
	}

	return (0);
}