#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_4__ {scalar_t__ nvl_priv; int nvl_nvflag; } ;
typedef  TYPE_1__ nvlist_t ;
typedef  int /*<<< orphan*/  data_type_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUP ; 
 int NV_UNIQUE_NAME ; 
 int NV_UNIQUE_NAME_TYPE ; 
 int nvpair_value_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * nvt_lookup_name_type (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvlist_lookup_common(nvlist_t *nvl, const char *name, data_type_t type,
    uint_t *nelem, void *data)
{
	if (name == NULL || nvl == NULL || nvl->nvl_priv == 0)
		return (EINVAL);

	if (!(nvl->nvl_nvflag & (NV_UNIQUE_NAME | NV_UNIQUE_NAME_TYPE)))
		return (ENOTSUP);

	nvpair_t *nvp = nvt_lookup_name_type(nvl, name, type);
	if (nvp == NULL)
		return (ENOENT);

	return (nvpair_value_common(nvp, type, nelem, data));
}