#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  nvstream_t ;
struct TYPE_6__ {size_t nvp_size; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
#define  DATA_TYPE_NVLIST 129 
#define  DATA_TYPE_NVLIST_ARRAY 128 
 int EINVAL ; 
 int /*<<< orphan*/  EMBEDDED_NVL (TYPE_1__*) ; 
 size_t INT32_MAX ; 
 int NVP_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  nvs_embedded_nvl_array (int /*<<< orphan*/ *,TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  nvs_operation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
nvs_native_nvp_size(nvstream_t *nvs, nvpair_t *nvp, size_t *size)
{
	uint64_t nvp_sz = nvp->nvp_size;

	switch (NVP_TYPE(nvp)) {
	case DATA_TYPE_NVLIST: {
		size_t nvsize = 0;

		if (nvs_operation(nvs, EMBEDDED_NVL(nvp), &nvsize) != 0)
			return (EINVAL);

		nvp_sz += nvsize;
		break;
	}
	case DATA_TYPE_NVLIST_ARRAY: {
		size_t nvsize;

		if (nvs_embedded_nvl_array(nvs, nvp, &nvsize) != 0)
			return (EINVAL);

		nvp_sz += nvsize;
		break;
	}
	default:
		break;
	}

	if (nvp_sz > INT32_MAX)
		return (EINVAL);

	*size = nvp_sz;

	return (0);
}