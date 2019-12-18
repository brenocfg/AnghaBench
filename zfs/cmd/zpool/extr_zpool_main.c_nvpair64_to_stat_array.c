#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat_array {int count; int /*<<< orphan*/  __data; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
#define  DATA_TYPE_UINT64 129 
#define  DATA_TYPE_UINT64_ARRAY 128 
 int EINVAL ; 
 scalar_t__ nvlist_lookup_nvpair (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int nvpair_value_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvpair_value_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  verify (int) ; 

__attribute__((used)) static int
nvpair64_to_stat_array(nvlist_t *nvl, const char *name,
    struct stat_array *nva)
{
	nvpair_t *tmp;
	int ret;

	verify(nvlist_lookup_nvpair(nvl, name, &tmp) == 0);
	switch (nvpair_type(tmp)) {
	case DATA_TYPE_UINT64_ARRAY:
		ret = nvpair_value_uint64_array(tmp, &nva->data, &nva->count);
		break;
	case DATA_TYPE_UINT64:
		ret = nvpair_value_uint64(tmp, &nva->__data);
		nva->data = &nva->__data;
		nva->count = 1;
		break;
	default:
		/* Not a uint64_t */
		ret = EINVAL;
		break;
	}

	return (ret);
}