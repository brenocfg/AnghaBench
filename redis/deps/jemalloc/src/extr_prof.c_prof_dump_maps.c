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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 size_t PROF_DUMP_BUFSIZE ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  config_prof ; 
 scalar_t__ malloc_read_fd (int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * prof_dump_buf ; 
 size_t prof_dump_buf_end ; 
 scalar_t__ prof_dump_flush (int) ; 
 scalar_t__ prof_dump_write (int,char*) ; 
 int prof_getpid () ; 
 int prof_open_maps (char*,...) ; 

__attribute__((used)) static bool
prof_dump_maps(bool propagate_err) {
	bool ret;
	int mfd;

	cassert(config_prof);
#ifdef __FreeBSD__
	mfd = prof_open_maps("/proc/curproc/map");
#elif defined(_WIN32)
	mfd = -1; // Not implemented
#else
	{
		int pid = prof_getpid();

		mfd = prof_open_maps("/proc/%d/task/%d/maps", pid, pid);
		if (mfd == -1) {
			mfd = prof_open_maps("/proc/%d/maps", pid);
		}
	}
#endif
	if (mfd != -1) {
		ssize_t nread;

		if (prof_dump_write(propagate_err, "\nMAPPED_LIBRARIES:\n") &&
		    propagate_err) {
			ret = true;
			goto label_return;
		}
		nread = 0;
		do {
			prof_dump_buf_end += nread;
			if (prof_dump_buf_end == PROF_DUMP_BUFSIZE) {
				/* Make space in prof_dump_buf before read(). */
				if (prof_dump_flush(propagate_err) &&
				    propagate_err) {
					ret = true;
					goto label_return;
				}
			}
			nread = malloc_read_fd(mfd,
			    &prof_dump_buf[prof_dump_buf_end], PROF_DUMP_BUFSIZE
			    - prof_dump_buf_end);
		} while (nread > 0);
	} else {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	if (mfd != -1) {
		close(mfd);
	}
	return ret;
}