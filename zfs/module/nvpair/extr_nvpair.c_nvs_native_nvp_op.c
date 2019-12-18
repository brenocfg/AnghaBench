#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int nvs_op; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_17__ {scalar_t__ nvp_size; int /*<<< orphan*/  nvp_name_sz; } ;
typedef  TYPE_2__ nvpair_t ;
typedef  int data_type_t ;

/* Variables and functions */
#define  DATA_TYPE_NVLIST 132 
#define  DATA_TYPE_NVLIST_ARRAY 131 
#define  DATA_TYPE_STRING_ARRAY 130 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  NVP_NELEM (TYPE_2__*) ; 
 scalar_t__ NVP_SIZE_CALC (int /*<<< orphan*/ ,int) ; 
 int NVP_TYPE (TYPE_2__*) ; 
#define  NVS_OP_DECODE 129 
#define  NVS_OP_ENCODE 128 
 int i_get_value_size (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ i_validate_nvpair_name (TYPE_2__*) ; 
 int /*<<< orphan*/  native_cp (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int nvpair_native_embedded (TYPE_1__*,TYPE_2__*) ; 
 int nvpair_native_embedded_array (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nvpair_native_string_array (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int
nvs_native_nvp_op(nvstream_t *nvs, nvpair_t *nvp)
{
	data_type_t type;
	int value_sz;
	int ret = 0;

	/*
	 * We do the initial bcopy of the data before we look at
	 * the nvpair type, because when we're decoding, we won't
	 * have the correct values for the pair until we do the bcopy.
	 */
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
	case NVS_OP_DECODE:
		if (native_cp(nvs, nvp, nvp->nvp_size) != 0)
			return (EFAULT);
		break;
	default:
		return (EINVAL);
	}

	/* verify nvp_name_sz, check the name string length */
	if (i_validate_nvpair_name(nvp) != 0)
		return (EFAULT);

	type = NVP_TYPE(nvp);

	/*
	 * Verify type and nelem and get the value size.
	 * In case of data types DATA_TYPE_STRING and DATA_TYPE_STRING_ARRAY
	 * is the size of the string(s) excluded.
	 */
	if ((value_sz = i_get_value_size(type, NULL, NVP_NELEM(nvp))) < 0)
		return (EFAULT);

	if (NVP_SIZE_CALC(nvp->nvp_name_sz, value_sz) > nvp->nvp_size)
		return (EFAULT);

	switch (type) {
	case DATA_TYPE_NVLIST:
		ret = nvpair_native_embedded(nvs, nvp);
		break;
	case DATA_TYPE_NVLIST_ARRAY:
		ret = nvpair_native_embedded_array(nvs, nvp);
		break;
	case DATA_TYPE_STRING_ARRAY:
		nvpair_native_string_array(nvs, nvp);
		break;
	default:
		break;
	}

	return (ret);
}