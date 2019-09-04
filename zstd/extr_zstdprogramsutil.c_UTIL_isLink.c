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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */

U32 UTIL_isLink(const char* infilename)
{
/* macro guards, as defined in : https://linux.die.net/man/2/lstat */
#ifndef __STRICT_ANSI__
#if defined(_BSD_SOURCE) \
    || (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)) \
    || (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) \
    || (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L)) \
    || (defined(__APPLE__) && defined(__MACH__)) \
    || defined(__OpenBSD__) \
    || defined(__FreeBSD__)
    int r;
    stat_t statbuf;
    r = lstat(infilename, &statbuf);
    if (!r && S_ISLNK(statbuf.st_mode)) return 1;
#endif
#endif
    (void)infilename;
    return 0;
}