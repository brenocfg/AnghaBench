#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct drr_free {scalar_t__ drr_object; scalar_t__ drr_offset; scalar_t__ drr_length; int /*<<< orphan*/  drr_toguid; } ;
struct TYPE_7__ {scalar_t__ dsc_last_data_object; scalar_t__ dsc_last_data_offset; scalar_t__ dsc_pending_op; int /*<<< orphan*/  dsc_toguid; TYPE_5__* dsc_drr; } ;
typedef  TYPE_2__ dmu_send_cookie_t ;
typedef  int /*<<< orphan*/  dmu_replay_record_t ;
struct TYPE_6__ {struct drr_free drr_free; } ;
struct TYPE_8__ {int /*<<< orphan*/  drr_type; TYPE_1__ drr_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DMU_OBJECT_END ; 
 int /*<<< orphan*/  DRR_FREE ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ PENDING_FREE ; 
 scalar_t__ PENDING_NONE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 scalar_t__ dump_record (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_free(dmu_send_cookie_t *dscp, uint64_t object, uint64_t offset,
    uint64_t length)
{
	struct drr_free *drrf = &(dscp->dsc_drr->drr_u.drr_free);

	/*
	 * When we receive a free record, dbuf_free_range() assumes
	 * that the receiving system doesn't have any dbufs in the range
	 * being freed.  This is always true because there is a one-record
	 * constraint: we only send one WRITE record for any given
	 * object,offset.  We know that the one-record constraint is
	 * true because we always send data in increasing order by
	 * object,offset.
	 *
	 * If the increasing-order constraint ever changes, we should find
	 * another way to assert that the one-record constraint is still
	 * satisfied.
	 */
	ASSERT(object > dscp->dsc_last_data_object ||
	    (object == dscp->dsc_last_data_object &&
	    offset > dscp->dsc_last_data_offset));

	/*
	 * If there is a pending op, but it's not PENDING_FREE, push it out,
	 * since free block aggregation can only be done for blocks of the
	 * same type (i.e., DRR_FREE records can only be aggregated with
	 * other DRR_FREE records.  DRR_FREEOBJECTS records can only be
	 * aggregated with other DRR_FREEOBJECTS records).
	 */
	if (dscp->dsc_pending_op != PENDING_NONE &&
	    dscp->dsc_pending_op != PENDING_FREE) {
		if (dump_record(dscp, NULL, 0) != 0)
			return (SET_ERROR(EINTR));
		dscp->dsc_pending_op = PENDING_NONE;
	}

	if (dscp->dsc_pending_op == PENDING_FREE) {
		/*
		 * Check to see whether this free block can be aggregated
		 * with pending one.
		 */
		if (drrf->drr_object == object && drrf->drr_offset +
		    drrf->drr_length == offset) {
			if (offset + length < offset || length == UINT64_MAX)
				drrf->drr_length = UINT64_MAX;
			else
				drrf->drr_length += length;
			return (0);
		} else {
			/* not a continuation.  Push out pending record */
			if (dump_record(dscp, NULL, 0) != 0)
				return (SET_ERROR(EINTR));
			dscp->dsc_pending_op = PENDING_NONE;
		}
	}
	/* create a FREE record and make it pending */
	bzero(dscp->dsc_drr, sizeof (dmu_replay_record_t));
	dscp->dsc_drr->drr_type = DRR_FREE;
	drrf->drr_object = object;
	drrf->drr_offset = offset;
	if (offset + length < offset)
		drrf->drr_length = DMU_OBJECT_END;
	else
		drrf->drr_length = length;
	drrf->drr_toguid = dscp->dsc_toguid;
	if (length == DMU_OBJECT_END) {
		if (dump_record(dscp, NULL, 0) != 0)
			return (SET_ERROR(EINTR));
	} else {
		dscp->dsc_pending_op = PENDING_FREE;
	}

	return (0);
}