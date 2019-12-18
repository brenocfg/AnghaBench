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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ddi_copyin (void*,char*,scalar_t__,int) ; 
 int nvlist_unpack (char*,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 char* vmem_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (char*,scalar_t__) ; 

__attribute__((used)) static int
get_nvlist(uint64_t nvl, uint64_t size, int iflag, nvlist_t **nvp)
{
	char *packed;
	int error;
	nvlist_t *list = NULL;

	/*
	 * Read in and unpack the user-supplied nvlist.
	 */
	if (size == 0)
		return (SET_ERROR(EINVAL));

	packed = vmem_alloc(size, KM_SLEEP);

	if ((error = ddi_copyin((void *)(uintptr_t)nvl, packed, size,
	    iflag)) != 0) {
		vmem_free(packed, size);
		return (SET_ERROR(EFAULT));
	}

	if ((error = nvlist_unpack(packed, size, &list, 0)) != 0) {
		vmem_free(packed, size);
		return (error);
	}

	vmem_free(packed, size);

	*nvp = list;
	return (0);
}