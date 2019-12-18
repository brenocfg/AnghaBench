#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode {int dummy; } ;
struct TYPE_3__ {scalar_t__ ddr_last; scalar_t__ ddr_first; int /*<<< orphan*/  ddr_type; } ;
struct diffarg {int da_err; TYPE_1__ da_ddr; int /*<<< orphan*/ * da_offp; struct vnode* da_vp; } ;
typedef  int /*<<< orphan*/  offset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_4__ {int /*<<< orphan*/  ds_creation_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDR_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int TRAVERSE_NO_DECRYPT ; 
 int TRAVERSE_PRE ; 
 int TRAVERSE_PREFETCH_METADATA ; 
 int /*<<< orphan*/  diff_cb ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_is_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_long_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_long_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int traverse_dataset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct diffarg*) ; 
 int /*<<< orphan*/  write_record (struct diffarg*) ; 

int
dmu_diff(const char *tosnap_name, const char *fromsnap_name,
    struct vnode *vp, offset_t *offp)
{
	struct diffarg da;
	dsl_dataset_t *fromsnap;
	dsl_dataset_t *tosnap;
	dsl_pool_t *dp;
	int error;
	uint64_t fromtxg;

	if (strchr(tosnap_name, '@') == NULL ||
	    strchr(fromsnap_name, '@') == NULL)
		return (SET_ERROR(EINVAL));

	error = dsl_pool_hold(tosnap_name, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, tosnap_name, FTAG, &tosnap);
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	error = dsl_dataset_hold(dp, fromsnap_name, FTAG, &fromsnap);
	if (error != 0) {
		dsl_dataset_rele(tosnap, FTAG);
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	if (!dsl_dataset_is_before(tosnap, fromsnap, 0)) {
		dsl_dataset_rele(fromsnap, FTAG);
		dsl_dataset_rele(tosnap, FTAG);
		dsl_pool_rele(dp, FTAG);
		return (SET_ERROR(EXDEV));
	}

	fromtxg = dsl_dataset_phys(fromsnap)->ds_creation_txg;
	dsl_dataset_rele(fromsnap, FTAG);

	dsl_dataset_long_hold(tosnap, FTAG);
	dsl_pool_rele(dp, FTAG);

	da.da_vp = vp;
	da.da_offp = offp;
	da.da_ddr.ddr_type = DDR_NONE;
	da.da_ddr.ddr_first = da.da_ddr.ddr_last = 0;
	da.da_err = 0;

	/*
	 * Since zfs diff only looks at dnodes which are stored in plaintext
	 * (other than bonus buffers), we don't technically need to decrypt
	 * the dataset to perform this operation. However, the command line
	 * utility will still fail if the keys are not loaded because the
	 * dataset isn't mounted and because it will fail when it attempts to
	 * call the ZFS_IOC_OBJ_TO_STATS ioctl.
	 */
	error = traverse_dataset(tosnap, fromtxg,
	    TRAVERSE_PRE | TRAVERSE_PREFETCH_METADATA | TRAVERSE_NO_DECRYPT,
	    diff_cb, &da);

	if (error != 0) {
		da.da_err = error;
	} else {
		/* we set the da.da_err we return as side-effect */
		(void) write_record(&da);
	}

	dsl_dataset_long_rele(tosnap, FTAG);
	dsl_dataset_rele(tosnap, FTAG);

	return (da.da_err);
}