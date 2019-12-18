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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETPIPE_SZ ; 
 int /*<<< orphan*/  F_SETPIPE_SZ ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 long fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fscanf (int /*<<< orphan*/ *,char*,unsigned long*) ; 

void
libzfs_set_pipe_max(int infd)
{
	FILE *procf = fopen("/proc/sys/fs/pipe-max-size", "r");

	if (procf != NULL) {
		unsigned long max_psize;
		long cur_psize;
		if (fscanf(procf, "%lu", &max_psize) > 0) {
			cur_psize = fcntl(infd, F_GETPIPE_SZ);
			if (cur_psize > 0 &&
			    max_psize > (unsigned long) cur_psize)
				fcntl(infd, F_SETPIPE_SZ,
				    max_psize);
		}
		fclose(procf);
	}
}