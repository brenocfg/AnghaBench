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

/* Variables and functions */
 int MSVCRT_FD_BLOCK_SIZE ; 
 int MSVCRT_MAX_FILES ; 
 int /*<<< orphan*/  __badioinfo ; 
 int /*<<< orphan*/ ** __pioinfo ; 

__attribute__((used)) static inline ioinfo* get_ioinfo_nolock(int fd)
{
    ioinfo *ret = NULL;
    if(fd>=0 && fd<MSVCRT_MAX_FILES)
        ret = __pioinfo[fd/MSVCRT_FD_BLOCK_SIZE];
    if(!ret)
        return &__badioinfo;

    return ret + (fd%MSVCRT_FD_BLOCK_SIZE);
}