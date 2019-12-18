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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dataset ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  ZFS_IOC_CREATE ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void
test_create(const char *pool)
{
	char dataset[MAXNAMELEN + 32];

	(void) snprintf(dataset, sizeof (dataset), "%s/create-fs", pool);

	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();
	nvlist_t *props = fnvlist_alloc();

	fnvlist_add_int32(required, "type", DMU_OST_ZFS);
	fnvlist_add_uint64(props, "recordsize", 8192);
	fnvlist_add_nvlist(optional, "props", props);

	IOC_INPUT_TEST(ZFS_IOC_CREATE, dataset, required, optional, 0);

	nvlist_free(required);
	nvlist_free(optional);
}