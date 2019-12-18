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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  fdpath ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 long INT_MAX ; 
 long OPEN_MAX ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 long dirfd (int /*<<< orphan*/ *) ; 
 long getdtablesize () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,long) ; 
 long strtol (char*,char**,int) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

void
closefrom(int lowfd)
{
    long fd, maxfd;
#if defined(HAVE_DIRFD) && defined(HAVE_PROC_PID)
    char fdpath[PATH_MAX], *endp;
    struct dirent *dent;
    DIR *dirp;
    int len;

    /* Check for a /proc/$$/fd directory. */
    len = snprintf(fdpath, sizeof(fdpath), "/proc/%ld/fd", (long)getpid());
    if (len > 0 && (size_t)len <= sizeof(fdpath) && (dirp = opendir(fdpath))) {
	while ((dent = readdir(dirp)) != NULL) {
	    fd = strtol(dent->d_name, &endp, 10);
	    if (dent->d_name != endp && *endp == '\0' &&
		fd >= 0 && fd < INT_MAX && fd >= lowfd && fd != dirfd(dirp))
		(void) close((int) fd);
	}
	(void) closedir(dirp);
    } else
#endif
    {
	/*
	 * Fall back on sysconf() or getdtablesize().  We avoid checking
	 * resource limits since it is possible to open a file descriptor
	 * and then drop the rlimit such that it is below the open fd.
	 */
#ifdef HAVE_SYSCONF
	maxfd = sysconf(_SC_OPEN_MAX);
#else
	maxfd = getdtablesize();
#endif /* HAVE_SYSCONF */
	if (maxfd < 0)
	    maxfd = OPEN_MAX;

	for (fd = lowfd; fd < maxfd; fd++)
	    (void) close((int) fd);
    }
}