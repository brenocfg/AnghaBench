#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nvp_size; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int /*<<< orphan*/  data_type_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  NVP_NELEM (TYPE_1__*) ; 
 int /*<<< orphan*/  NVP_TYPE (TYPE_1__*) ; 
 int NVP_VALOFF (TYPE_1__*) ; 
 int /*<<< orphan*/  NVP_VALUE (TYPE_1__*) ; 
 int NV_ALIGN (int) ; 
 int i_get_value_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i_validate_nvpair_name (TYPE_1__*) ; 
 scalar_t__ i_validate_nvpair_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i_validate_nvpair(nvpair_t *nvp)
{
	data_type_t type = NVP_TYPE(nvp);
	int size1, size2;

	/* verify nvp_name_sz, check the name string length */
	if (i_validate_nvpair_name(nvp) != 0)
		return (EFAULT);

	if (i_validate_nvpair_value(type, NVP_NELEM(nvp), NVP_VALUE(nvp)) != 0)
		return (EFAULT);

	/*
	 * verify nvp_type, nvp_value_elem, and also possibly
	 * verify string values and get the value size.
	 */
	size2 = i_get_value_size(type, NVP_VALUE(nvp), NVP_NELEM(nvp));
	size1 = nvp->nvp_size - NVP_VALOFF(nvp);
	if (size2 < 0 || size1 != NV_ALIGN(size2))
		return (EFAULT);

	return (0);
}