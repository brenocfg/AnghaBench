#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  drc_os; } ;
typedef  TYPE_1__ dmu_recv_cookie_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS_FIELD_RESUME_OBJECT ; 
 int /*<<< orphan*/  DS_FIELD_RESUME_OFFSET ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_id (int /*<<< orphan*/ ) ; 
 TYPE_3__* dmu_objset_pool (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  zap_lookup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static int
resume_check(dmu_recv_cookie_t *drc, nvlist_t *begin_nvl)
{
	uint64_t val;
	objset_t *mos = dmu_objset_pool(drc->drc_os)->dp_meta_objset;
	uint64_t dsobj = dmu_objset_id(drc->drc_os);
	uint64_t resume_obj, resume_off;

	if (nvlist_lookup_uint64(begin_nvl,
	    "resume_object", &resume_obj) != 0 ||
	    nvlist_lookup_uint64(begin_nvl,
	    "resume_offset", &resume_off) != 0) {
		return (SET_ERROR(EINVAL));
	}
	VERIFY0(zap_lookup(mos, dsobj,
	    DS_FIELD_RESUME_OBJECT, sizeof (val), 1, &val));
	if (resume_obj != val)
		return (SET_ERROR(EINVAL));
	VERIFY0(zap_lookup(mos, dsobj,
	    DS_FIELD_RESUME_OFFSET, sizeof (val), 1, &val));
	if (resume_off != val)
		return (SET_ERROR(EINVAL));

	return (0);
}