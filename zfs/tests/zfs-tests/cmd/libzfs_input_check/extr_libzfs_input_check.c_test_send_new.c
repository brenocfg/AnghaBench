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

/* Variables and functions */
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_IOC_SEND_NEW ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  from ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offset ; 
 int /*<<< orphan*/  resumeobj ; 

__attribute__((used)) static void
test_send_new(const char *snapshot, int fd)
{
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();

	fnvlist_add_int32(required, "fd", fd);

	fnvlist_add_boolean(optional, "largeblockok");
	fnvlist_add_boolean(optional, "embedok");
	fnvlist_add_boolean(optional, "compressok");
	fnvlist_add_boolean(optional, "rawok");

	/*
	 * TODO - Resumable send is harder to set up. So we currently
	 * ignore testing for that variant.
	 */
#if 0
	fnvlist_add_string(optional, "fromsnap", from);
	fnvlist_add_uint64(optional, "resume_object", resumeobj);
	fnvlist_add_uint64(optional, "resume_offset", offset);
#endif
	IOC_INPUT_TEST(ZFS_IOC_SEND_NEW, snapshot, required, optional, 0);

	nvlist_free(optional);
	nvlist_free(required);
}