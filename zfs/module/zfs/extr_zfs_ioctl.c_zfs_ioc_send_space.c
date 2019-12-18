#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ zbm_redaction_obj; scalar_t__ zbm_guid; int zbm_flags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_bookmark_phys_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  offset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_8__ {void* dso_dryrun; scalar_t__* dso_arg; int /*<<< orphan*/  dso_outfunc; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ dmu_send_outparams_t ;
typedef  int boolean_t ;
struct TYPE_9__ {scalar_t__ ds_guid; } ;

/* Variables and functions */
 int B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZBM_FLAG_HAS_FBN ; 
 int dmu_send (char const*,char*,int,int,int,int,scalar_t__,scalar_t__,char*,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int dmu_send_estimate_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__*) ; 
 int dsl_bookmark_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_is_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_lookup_int32 (int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  send_space_sum ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static int
zfs_ioc_send_space(const char *snapname, nvlist_t *innvl, nvlist_t *outnvl)
{
	dsl_pool_t *dp;
	dsl_dataset_t *tosnap;
	dsl_dataset_t *fromsnap = NULL;
	int error;
	char *fromname = NULL;
	char *redactlist_book = NULL;
	boolean_t largeblockok;
	boolean_t embedok;
	boolean_t compressok;
	boolean_t rawok;
	uint64_t space = 0;
	boolean_t full_estimate = B_FALSE;
	uint64_t resumeobj = 0;
	uint64_t resumeoff = 0;
	uint64_t resume_bytes = 0;
	int32_t fd = -1;
	zfs_bookmark_phys_t zbm = {0};

	error = dsl_pool_hold(snapname, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, snapname, FTAG, &tosnap);
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}
	(void) nvlist_lookup_int32(innvl, "fd", &fd);

	largeblockok = nvlist_exists(innvl, "largeblockok");
	embedok = nvlist_exists(innvl, "embedok");
	compressok = nvlist_exists(innvl, "compressok");
	rawok = nvlist_exists(innvl, "rawok");
	boolean_t from = (nvlist_lookup_string(innvl, "from", &fromname) == 0);
	boolean_t altbook = (nvlist_lookup_string(innvl, "redactbook",
	    &redactlist_book) == 0);

	(void) nvlist_lookup_uint64(innvl, "resume_object", &resumeobj);
	(void) nvlist_lookup_uint64(innvl, "resume_offset", &resumeoff);
	(void) nvlist_lookup_uint64(innvl, "bytes", &resume_bytes);

	if (altbook) {
		full_estimate = B_TRUE;
	} else if (from) {
		if (strchr(fromname, '#')) {
			error = dsl_bookmark_lookup(dp, fromname, tosnap, &zbm);

			/*
			 * dsl_bookmark_lookup() will fail with EXDEV if
			 * the from-bookmark and tosnap are at the same txg.
			 * However, it's valid to do a send (and therefore,
			 * a send estimate) from and to the same time point,
			 * if the bookmark is redacted (the incremental send
			 * can change what's redacted on the target).  In
			 * this case, dsl_bookmark_lookup() fills in zbm
			 * but returns EXDEV.  Ignore this error.
			 */
			if (error == EXDEV && zbm.zbm_redaction_obj != 0 &&
			    zbm.zbm_guid ==
			    dsl_dataset_phys(tosnap)->ds_guid)
				error = 0;

			if (error != 0) {
				dsl_dataset_rele(tosnap, FTAG);
				dsl_pool_rele(dp, FTAG);
				return (error);
			}
			if (zbm.zbm_redaction_obj != 0 || !(zbm.zbm_flags &
			    ZBM_FLAG_HAS_FBN)) {
				full_estimate = B_TRUE;
			}
		} else if (strchr(fromname, '@')) {
			error = dsl_dataset_hold(dp, fromname, FTAG, &fromsnap);
			if (error != 0) {
				dsl_dataset_rele(tosnap, FTAG);
				dsl_pool_rele(dp, FTAG);
				return (error);
			}

			if (!dsl_dataset_is_before(tosnap, fromsnap, 0)) {
				full_estimate = B_TRUE;
				dsl_dataset_rele(fromsnap, FTAG);
			}
		} else {
			/*
			 * from is not properly formatted as a snapshot or
			 * bookmark
			 */
			dsl_dataset_rele(tosnap, FTAG);
			dsl_pool_rele(dp, FTAG);
			return (SET_ERROR(EINVAL));
		}
	}

	if (full_estimate) {
		dmu_send_outparams_t out = {0};
		offset_t off = 0;
		out.dso_outfunc = send_space_sum;
		out.dso_arg = &space;
		out.dso_dryrun = B_TRUE;
		/*
		 * We have to release these holds so dmu_send can take them.  It
		 * will do all the error checking we need.
		 */
		dsl_dataset_rele(tosnap, FTAG);
		dsl_pool_rele(dp, FTAG);
		error = dmu_send(snapname, fromname, embedok, largeblockok,
		    compressok, rawok, resumeobj, resumeoff, redactlist_book,
		    fd, &off, &out);
	} else {
		error = dmu_send_estimate_fast(tosnap, fromsnap,
		    (from && strchr(fromname, '#') != NULL ? &zbm : NULL),
		    compressok || rawok, &space);
		space -= resume_bytes;
		if (fromsnap != NULL)
			dsl_dataset_rele(fromsnap, FTAG);
		dsl_dataset_rele(tosnap, FTAG);
		dsl_pool_rele(dp, FTAG);
	}

	fnvlist_add_uint64(outnvl, "space", space);

	return (error);
}