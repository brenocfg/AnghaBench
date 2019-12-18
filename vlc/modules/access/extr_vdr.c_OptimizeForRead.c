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
 int /*<<< orphan*/  F_NOCACHE ; 
 int /*<<< orphan*/  F_RDAHEAD ; 
 int /*<<< orphan*/  POSIX_FADV_NOREUSE ; 
 int /*<<< orphan*/  POSIX_FADV_WILLNEED ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  posix_fadvise (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OptimizeForRead( int fd )
{
    /* cf. Open() in file access module */
    VLC_UNUSED(fd);
#ifdef HAVE_POSIX_FADVISE
    posix_fadvise( fd, 0, 4096, POSIX_FADV_WILLNEED );
    posix_fadvise( fd, 0, 0, POSIX_FADV_NOREUSE );
#endif
#ifdef F_RDAHEAD
    fcntl( fd, F_RDAHEAD, 1 );
#endif
#ifdef F_NOCACHE
    fcntl( fd, F_NOCACHE, 0 );
#endif
}