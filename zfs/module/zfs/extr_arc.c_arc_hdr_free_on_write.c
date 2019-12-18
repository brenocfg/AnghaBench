#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  arcs_size; int /*<<< orphan*/ * arcs_esize; } ;
typedef  TYPE_3__ arc_state_t ;
struct TYPE_13__ {int /*<<< orphan*/  b_pabd; int /*<<< orphan*/  b_refcnt; int /*<<< orphan*/  b_arc_node; TYPE_3__* b_state; } ;
struct TYPE_12__ {int /*<<< orphan*/  b_rabd; } ;
struct TYPE_15__ {TYPE_2__ b_l1hdr; TYPE_1__ b_crypt_hdr; } ;
typedef  TYPE_4__ arc_buf_hdr_t ;
typedef  size_t arc_buf_contents_t ;

/* Variables and functions */
 size_t ARC_BUFC_DATA ; 
 size_t ARC_BUFC_METADATA ; 
 int /*<<< orphan*/  ARC_SPACE_DATA ; 
 int /*<<< orphan*/  ARC_SPACE_META ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  HDR_GET_PSIZE (TYPE_4__*) ; 
 TYPE_3__* arc_anon ; 
 size_t arc_buf_type (TYPE_4__*) ; 
 int /*<<< orphan*/  arc_hdr_size (TYPE_4__*) ; 
 TYPE_3__* arc_l2c_only ; 
 int /*<<< orphan*/  arc_space_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2arc_free_abd_on_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ multilist_link_active (int /*<<< orphan*/ *) ; 
 int zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_remove_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
arc_hdr_free_on_write(arc_buf_hdr_t *hdr, boolean_t free_rdata)
{
	arc_state_t *state = hdr->b_l1hdr.b_state;
	arc_buf_contents_t type = arc_buf_type(hdr);
	uint64_t size = (free_rdata) ? HDR_GET_PSIZE(hdr) : arc_hdr_size(hdr);

	/* protected by hash lock, if in the hash table */
	if (multilist_link_active(&hdr->b_l1hdr.b_arc_node)) {
		ASSERT(zfs_refcount_is_zero(&hdr->b_l1hdr.b_refcnt));
		ASSERT(state != arc_anon && state != arc_l2c_only);

		(void) zfs_refcount_remove_many(&state->arcs_esize[type],
		    size, hdr);
	}
	(void) zfs_refcount_remove_many(&state->arcs_size, size, hdr);
	if (type == ARC_BUFC_METADATA) {
		arc_space_return(size, ARC_SPACE_META);
	} else {
		ASSERT(type == ARC_BUFC_DATA);
		arc_space_return(size, ARC_SPACE_DATA);
	}

	if (free_rdata) {
		l2arc_free_abd_on_write(hdr->b_crypt_hdr.b_rabd, size, type);
	} else {
		l2arc_free_abd_on_write(hdr->b_l1hdr.b_pabd, size, type);
	}
}