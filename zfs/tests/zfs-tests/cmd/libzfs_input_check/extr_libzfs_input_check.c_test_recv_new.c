#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  snapshot ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  drr ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dmu_replay_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADE ; 
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  ZFS_IOC_RECV_NEW ; 
 int /*<<< orphan*/ * action_handle ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_add_byte_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* origin ; 
 int pread (int,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * recvdprops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_recv_new(const char *dataset, int fd)
{
	dmu_replay_record_t drr = { 0 };
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();
	nvlist_t *props = fnvlist_alloc();
	char snapshot[MAXNAMELEN + 32];
	ssize_t count;

	int cleanup_fd = open(ZFS_DEV, O_RDWR);

	(void) snprintf(snapshot, sizeof (snapshot), "%s@replicant", dataset);

	count = pread(fd, &drr, sizeof (drr), 0);
	if (count != sizeof (drr)) {
		(void) fprintf(stderr, "could not read stream: %s\n",
		    strerror(errno));
	}

	fnvlist_add_string(required, "snapname", snapshot);
	fnvlist_add_byte_array(required, "begin_record", (uchar_t *)&drr,
	    sizeof (drr));
	fnvlist_add_int32(required, "input_fd", fd);

	fnvlist_add_string(props, "org.openzfs:launch", "September 17th, 2013");
	fnvlist_add_nvlist(optional, "localprops", props);
	fnvlist_add_boolean(optional, "force");
	fnvlist_add_int32(optional, "cleanup_fd", cleanup_fd);

	/*
	 * TODO - Resumable receive is harder to set up. So we currently
	 * ignore testing for one.
	 */
#if 0
	fnvlist_add_nvlist(optional, "props", recvdprops);
	fnvlist_add_string(optional, "origin", origin);
	fnvlist_add_boolean(optional, "resumable");
	fnvlist_add_uint64(optional, "action_handle", *action_handle);
#endif
	IOC_INPUT_TEST(ZFS_IOC_RECV_NEW, dataset, required, optional, EBADE);

	nvlist_free(props);
	nvlist_free(optional);
	nvlist_free(required);

	(void) close(cleanup_fd);
}