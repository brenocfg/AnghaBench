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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_DIRECTORY ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int openat (int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int) ; 

DIR *xopendirat(int fd, const char *name, int flags) {
        int nfd;
        DIR *d;

        assert(!(flags & O_CREAT));

        nfd = openat(fd, name, O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC|flags, 0);
        if (nfd < 0)
                return NULL;

        d = fdopendir(nfd);
        if (!d) {
                safe_close(nfd);
                return NULL;
        }

        return d;
}