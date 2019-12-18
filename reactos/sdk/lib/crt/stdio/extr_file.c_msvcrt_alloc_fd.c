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
typedef  int /*<<< orphan*/  ioinfo ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __badioinfo ; 
 int /*<<< orphan*/ * get_ioinfo_alloc (int*) ; 
 int /*<<< orphan*/  msvcrt_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_ioinfo (int /*<<< orphan*/ *) ; 

int msvcrt_alloc_fd(HANDLE hand, int flag)
{
    int fd;
    ioinfo *info = get_ioinfo_alloc(&fd);

    TRACE(":handle (%p) allocating fd (%d)\n", hand, fd);

    if(info == &__badioinfo)
        return -1;

    msvcrt_set_fd(info, hand, flag);
    release_ioinfo(info);
    return fd;
}