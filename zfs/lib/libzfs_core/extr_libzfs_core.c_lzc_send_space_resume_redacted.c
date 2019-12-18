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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;

/* Variables and functions */
 int LZC_SEND_FLAG_COMPRESS ; 
 int LZC_SEND_FLAG_EMBED_DATA ; 
 int LZC_SEND_FLAG_LARGE_BLOCK ; 
 int LZC_SEND_FLAG_RAW ; 
 int /*<<< orphan*/  ZFS_IOC_SEND_SPACE ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_lookup_uint64 (int /*<<< orphan*/ *,char*) ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

int
lzc_send_space_resume_redacted(const char *snapname, const char *from,
    enum lzc_send_flags flags, uint64_t resumeobj, uint64_t resumeoff,
    uint64_t resume_bytes, const char *redactbook, int fd, uint64_t *spacep)
{
	nvlist_t *args;
	nvlist_t *result;
	int err;

	args = fnvlist_alloc();
	if (from != NULL)
		fnvlist_add_string(args, "from", from);
	if (flags & LZC_SEND_FLAG_LARGE_BLOCK)
		fnvlist_add_boolean(args, "largeblockok");
	if (flags & LZC_SEND_FLAG_EMBED_DATA)
		fnvlist_add_boolean(args, "embedok");
	if (flags & LZC_SEND_FLAG_COMPRESS)
		fnvlist_add_boolean(args, "compressok");
	if (flags & LZC_SEND_FLAG_RAW)
		fnvlist_add_boolean(args, "rawok");
	if (resumeobj != 0 || resumeoff != 0) {
		fnvlist_add_uint64(args, "resume_object", resumeobj);
		fnvlist_add_uint64(args, "resume_offset", resumeoff);
		fnvlist_add_uint64(args, "bytes", resume_bytes);
	}
	if (redactbook != NULL)
		fnvlist_add_string(args, "redactbook", redactbook);
	if (fd != -1)
		fnvlist_add_int32(args, "fd", fd);

	err = lzc_ioctl(ZFS_IOC_SEND_SPACE, snapname, args, &result);
	nvlist_free(args);
	if (err == 0)
		*spacep = fnvlist_lookup_uint64(result, "space");
	nvlist_free(result);
	return (err);
}