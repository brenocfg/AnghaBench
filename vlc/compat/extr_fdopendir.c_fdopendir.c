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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
#define  EACCES 133 
 int EBADF ; 
 int EIO ; 
#define  ELOOP 132 
#define  EMFILE 131 
#define  ENAMETOOLONG 130 
#define  ENFILE 129 
#define  ENOENT 128 
 int ENOTDIR ; 
 int /*<<< orphan*/  F_GETFL ; 
 int O_ACCMODE ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

DIR *fdopendir (int fd)
{
#ifdef F_GETFL
    /* Check read permission on file descriptor */
    int mode = fcntl (fd, F_GETFL);
    if (mode == -1 || (mode & O_ACCMODE) == O_WRONLY)
    {
        errno = EBADF;
        return NULL;
    }
#endif
    /* Check directory file type */
    struct stat st;
    if (fstat (fd, &st))
        return NULL;

    if (!S_ISDIR (st.st_mode))
    {
        errno = ENOTDIR;
        return NULL;
    }

    /* Try to open the directory through /proc where available.
     * Not all operating systems support this. Fix your libc! */
    char path[sizeof ("/proc/self/fd/") + 3 * sizeof (int)];
    sprintf (path, "/proc/self/fd/%u", fd);

    DIR *dir = opendir (path);
    if (dir != NULL)
    {
        close (fd);
        return dir;
    }

    /* Hide impossible errors for fdopendir() */
    switch (errno)
    {
        case EACCES:
#ifdef ELOOP
        case ELOOP:
#endif
        case ENAMETOOLONG:
        case ENOENT:
        case EMFILE:
        case ENFILE:
            errno = EIO;
    }
    return NULL;
}