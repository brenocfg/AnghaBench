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

/* Variables and functions */
 int /*<<< orphan*/  LOCK_EX ; 
 int /*<<< orphan*/  LOCK_UN ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  flock (int,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int open (char const*,int,int) ; 
 int strlen (char const*) ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static int
open_trace(int devnull, const char *argv[])
{
	static const char *trace_file;

	if (!trace_file) {
		trace_file = getenv("TIG_TRACE");
		if (!trace_file)
			trace_file = "";
	}

	if (*trace_file) {
		int fd = open(trace_file, O_RDWR | O_CREAT | O_APPEND, 0666);
		int i;

		flock(fd, LOCK_EX);
		for (i = 0; argv[i]; i++) {
			if (write(fd, argv[i], strlen(argv[i])) == -1
			    || write(fd, " ", 1) == -1)
				break;
		}
		if (argv[i] || write(fd, "\n", 1) == -1) {
			flock(fd, LOCK_UN);
			close(fd);
			return devnull;
		}

		flock(fd, LOCK_UN);
		return fd;
	}

	return devnull;
}