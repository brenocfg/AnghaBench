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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ sa_force_spill; } ;
typedef  TYPE_1__ sa_os_t ;
typedef  int /*<<< orphan*/  sa_hdr_phys_t ;
struct TYPE_7__ {int /*<<< orphan*/  sa_attr; scalar_t__ sa_length; } ;
typedef  TYPE_2__ sa_bulk_attr_t ;
typedef  scalar_t__ sa_buf_type_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 scalar_t__ DMU_OT_ZNODE ; 
 int IS_P2ALIGNED (int,int) ; 
 int P2ROUNDUP (int,int) ; 
 scalar_t__ SA_BONUS ; 
 scalar_t__ SA_BONUSTYPE_FROM_DB (int /*<<< orphan*/ *) ; 
 scalar_t__ SA_REGISTERED_LEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SA_SPILL ; 

__attribute__((used)) static int
sa_find_sizes(sa_os_t *sa, sa_bulk_attr_t *attr_desc, int attr_count,
    dmu_buf_t *db, sa_buf_type_t buftype, int full_space, int *index,
    int *total, boolean_t *will_spill)
{
	int var_size_count = 0;
	int i;
	int hdrsize;
	int extra_hdrsize;

	if (buftype == SA_BONUS && sa->sa_force_spill) {
		*total = 0;
		*index = 0;
		*will_spill = B_TRUE;
		return (0);
	}

	*index = -1;
	*total = 0;
	*will_spill = B_FALSE;

	extra_hdrsize = 0;
	hdrsize = (SA_BONUSTYPE_FROM_DB(db) == DMU_OT_ZNODE) ? 0 :
	    sizeof (sa_hdr_phys_t);

	ASSERT(IS_P2ALIGNED(full_space, 8));

	for (i = 0; i != attr_count; i++) {
		boolean_t is_var_sz, might_spill_here;
		int tmp_hdrsize;

		*total = P2ROUNDUP(*total, 8);
		*total += attr_desc[i].sa_length;
		if (*will_spill)
			continue;

		is_var_sz = (SA_REGISTERED_LEN(sa, attr_desc[i].sa_attr) == 0);
		if (is_var_sz)
			var_size_count++;

		/*
		 * Calculate what the SA header size would be if this
		 * attribute doesn't spill.
		 */
		tmp_hdrsize = hdrsize + ((is_var_sz && var_size_count > 1) ?
		    sizeof (uint16_t) : 0);

		/*
		 * Check whether this attribute spans into the space
		 * that would be used by the spill block pointer should
		 * a spill block be needed.
		 */
		might_spill_here =
		    buftype == SA_BONUS && *index == -1 &&
		    (*total + P2ROUNDUP(tmp_hdrsize, 8)) >
		    (full_space - sizeof (blkptr_t));

		if (is_var_sz && var_size_count > 1) {
			if (buftype == SA_SPILL ||
			    tmp_hdrsize + *total < full_space) {
				/*
				 * Record the extra header size in case this
				 * increase needs to be reversed due to
				 * spill-over.
				 */
				hdrsize = tmp_hdrsize;
				if (*index != -1 || might_spill_here)
					extra_hdrsize += sizeof (uint16_t);
			} else {
				ASSERT(buftype == SA_BONUS);
				if (*index == -1)
					*index = i;
				*will_spill = B_TRUE;
				continue;
			}
		}

		/*
		 * Store index of where spill *could* occur. Then
		 * continue to count the remaining attribute sizes. The
		 * sum is used later for sizing bonus and spill buffer.
		 */
		if (might_spill_here)
			*index = i;

		if ((*total + P2ROUNDUP(hdrsize, 8)) > full_space &&
		    buftype == SA_BONUS)
			*will_spill = B_TRUE;
	}

	if (*will_spill)
		hdrsize -= extra_hdrsize;

	hdrsize = P2ROUNDUP(hdrsize, 8);
	return (hdrsize);
}