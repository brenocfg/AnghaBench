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
struct drr_redact {scalar_t__ drr_object; scalar_t__ drr_offset; scalar_t__ drr_length; int /*<<< orphan*/  drr_toguid; } ;
struct TYPE_7__ {scalar_t__ dsc_pending_op; int /*<<< orphan*/  dsc_toguid; TYPE_5__* dsc_drr; } ;
typedef  TYPE_2__ dmu_send_cookie_t ;
typedef  int /*<<< orphan*/  dmu_replay_record_t ;
struct TYPE_6__ {struct drr_redact drr_redact; } ;
struct TYPE_8__ {int /*<<< orphan*/  drr_type; TYPE_1__ drr_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRR_REDACT ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ PENDING_NONE ; 
 scalar_t__ PENDING_REDACT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 scalar_t__ dump_record (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_redact(dmu_send_cookie_t *dscp, uint64_t object, uint64_t offset,
    uint64_t length)
{
	struct drr_redact *drrr = &dscp->dsc_drr->drr_u.drr_redact;

	/*
	 * If there is a pending op, but it's not PENDING_REDACT, push it out,
	 * since free block aggregation can only be done for blocks of the
	 * same type (i.e., DRR_REDACT records can only be aggregated with
	 * other DRR_REDACT records).
	 */
	if (dscp->dsc_pending_op != PENDING_NONE &&
	    dscp->dsc_pending_op != PENDING_REDACT) {
		if (dump_record(dscp, NULL, 0) != 0)
			return (SET_ERROR(EINTR));
		dscp->dsc_pending_op = PENDING_NONE;
	}

	if (dscp->dsc_pending_op == PENDING_REDACT) {
		/*
		 * Check to see whether this redacted block can be aggregated
		 * with pending one.
		 */
		if (drrr->drr_object == object && drrr->drr_offset +
		    drrr->drr_length == offset) {
			drrr->drr_length += length;
			return (0);
		} else {
			/* not a continuation.  Push out pending record */
			if (dump_record(dscp, NULL, 0) != 0)
				return (SET_ERROR(EINTR));
			dscp->dsc_pending_op = PENDING_NONE;
		}
	}
	/* create a REDACT record and make it pending */
	bzero(dscp->dsc_drr, sizeof (dmu_replay_record_t));
	dscp->dsc_drr->drr_type = DRR_REDACT;
	drrr->drr_object = object;
	drrr->drr_offset = offset;
	drrr->drr_length = length;
	drrr->drr_toguid = dscp->dsc_toguid;
	dscp->dsc_pending_op = PENDING_REDACT;

	return (0);
}