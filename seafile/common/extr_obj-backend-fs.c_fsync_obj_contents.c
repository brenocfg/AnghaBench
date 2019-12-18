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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  F_FULLFSYNC ; 
 int /*<<< orphan*/  FlushFileBuffers (scalar_t__) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ _get_osfhandle (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int
fsync_obj_contents (int fd)
{
#ifdef __linux__
    /* Some file systems may not support fsync().
     * In this case, just skip the error.
     */
    if (fsync (fd) < 0) {
        if (errno == EINVAL)
            return 0;
        else {
            seaf_warning ("Failed to fsync: %s.\n", strerror(errno));
            return -1;
        }
    }
    return 0;
#endif

#ifdef __APPLE__
    /* OS X: fcntl() is required to flush disk cache, fsync() only
     * flushes operating system cache.
     */
    if (fcntl (fd, F_FULLFSYNC, NULL) < 0) {
        seaf_warning ("Failed to fsync: %s.\n", strerror(errno));
        return -1;
    }
    return 0;
#endif

#ifdef WIN32
    HANDLE handle;

    handle = (HANDLE)_get_osfhandle (fd);
    if (handle == INVALID_HANDLE_VALUE) {
        seaf_warning ("Failed to get handle from fd.\n");
        return -1;
    }

    if (!FlushFileBuffers (handle)) {
        seaf_warning ("FlushFileBuffer() failed: %lu.\n", GetLastError());
        return -1;
    }

    return 0;
#endif
}