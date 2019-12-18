#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  offset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_5__ {int /*<<< orphan*/  f_offset; int /*<<< orphan*/  f_vnode; } ;
typedef  TYPE_1__ file_t ;
struct TYPE_6__ {int /*<<< orphan*/  dso_dryrun; int /*<<< orphan*/  dso_arg; int /*<<< orphan*/  dso_outfunc; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ dmu_send_outparams_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EBADF ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_SEEK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_send (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dump_bytes ; 
 int fnvlist_lookup_int32 (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* getf (int) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releasef (int) ; 

__attribute__((used)) static int
zfs_ioc_send_new(const char *snapname, nvlist_t *innvl, nvlist_t *outnvl)
{
	int error;
	offset_t off;
	char *fromname = NULL;
	int fd;
	file_t *fp;
	boolean_t largeblockok;
	boolean_t embedok;
	boolean_t compressok;
	boolean_t rawok;
	uint64_t resumeobj = 0;
	uint64_t resumeoff = 0;
	char *redactbook = NULL;

	fd = fnvlist_lookup_int32(innvl, "fd");

	(void) nvlist_lookup_string(innvl, "fromsnap", &fromname);

	largeblockok = nvlist_exists(innvl, "largeblockok");
	embedok = nvlist_exists(innvl, "embedok");
	compressok = nvlist_exists(innvl, "compressok");
	rawok = nvlist_exists(innvl, "rawok");

	(void) nvlist_lookup_uint64(innvl, "resume_object", &resumeobj);
	(void) nvlist_lookup_uint64(innvl, "resume_offset", &resumeoff);

	(void) nvlist_lookup_string(innvl, "redactbook", &redactbook);

	if ((fp = getf(fd)) == NULL)
		return (SET_ERROR(EBADF));

	off = fp->f_offset;
	dmu_send_outparams_t out = {0};
	out.dso_outfunc = dump_bytes;
	out.dso_arg = fp->f_vnode;
	out.dso_dryrun = B_FALSE;
	error = dmu_send(snapname, fromname, embedok, largeblockok, compressok,
	    rawok, resumeobj, resumeoff, redactbook, fd, &off, &out);

	if (VOP_SEEK(fp->f_vnode, fp->f_offset, &off, NULL) == 0)
		fp->f_offset = off;

	releasef(fd);
	return (error);
}