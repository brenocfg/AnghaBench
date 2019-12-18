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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct drr_begin {scalar_t__ drr_fromguid; int /*<<< orphan*/  drr_toguid; int /*<<< orphan*/  drr_versioninfo; } ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_4__ {int /*<<< orphan*/  drc_begin_nvl; struct drr_begin* drc_drrb; } ;
typedef  TYPE_1__ dmu_recv_cookie_t ;
struct TYPE_5__ {TYPE_1__* drba_cookie; } ;
typedef  TYPE_2__ dmu_recv_begin_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEGINNV_REDACT_FROM_SNAPS ; 
 int /*<<< orphan*/  BEGINNV_REDACT_SNAPS ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int DMU_BACKUP_FEATURE_REDACTED ; 
 int DMU_GET_FEATUREFLAGS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPA_FEATURE_REDACTED_DATASETS ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compatible_redact_snaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_get_uint64_array_feature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int nvlist_lookup_uint64_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redact_snaps_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
redact_check(dmu_recv_begin_arg_t *drba, dsl_dataset_t *origin)
{
	uint64_t *origin_snaps;
	uint64_t origin_num_snaps;
	dmu_recv_cookie_t *drc = drba->drba_cookie;
	struct drr_begin *drrb = drc->drc_drrb;
	int featureflags = DMU_GET_FEATUREFLAGS(drrb->drr_versioninfo);
	int err = 0;
	boolean_t ret = B_TRUE;
	uint64_t *redact_snaps;
	uint_t numredactsnaps;

	/*
	 * If this is a full send stream, we're safe no matter what.
	 */
	if (drrb->drr_fromguid == 0)
		return (ret);

	VERIFY(dsl_dataset_get_uint64_array_feature(origin,
	    SPA_FEATURE_REDACTED_DATASETS, &origin_num_snaps, &origin_snaps));

	if (nvlist_lookup_uint64_array(drc->drc_begin_nvl,
	    BEGINNV_REDACT_FROM_SNAPS, &redact_snaps, &numredactsnaps) ==
	    0) {
		/*
		 * If the send stream was sent from the redaction bookmark or
		 * the redacted version of the dataset, then we're safe.  Verify
		 * that this is from the a compatible redaction bookmark or
		 * redacted dataset.
		 */
		if (!compatible_redact_snaps(origin_snaps, origin_num_snaps,
		    redact_snaps, numredactsnaps)) {
			err = EINVAL;
		}
	} else if (featureflags & DMU_BACKUP_FEATURE_REDACTED) {
		/*
		 * If the stream is redacted, it must be redacted with respect
		 * to a subset of what the origin is redacted with respect to.
		 * See case number 2 in the zfs man page section on redacted zfs
		 * send.
		 */
		err = nvlist_lookup_uint64_array(drc->drc_begin_nvl,
		    BEGINNV_REDACT_SNAPS, &redact_snaps, &numredactsnaps);

		if (err != 0 || !compatible_redact_snaps(origin_snaps,
		    origin_num_snaps, redact_snaps, numredactsnaps)) {
			err = EINVAL;
		}
	} else if (!redact_snaps_contains(origin_snaps, origin_num_snaps,
	    drrb->drr_toguid)) {
		/*
		 * If the stream isn't redacted but the origin is, this must be
		 * one of the snapshots the origin is redacted with respect to.
		 * See case number 1 in the zfs man page section on redacted zfs
		 * send.
		 */
		err = EINVAL;
	}

	if (err != 0)
		ret = B_FALSE;
	return (ret);
}