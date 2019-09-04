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
 int /*<<< orphan*/  __badioinfo ; 
 int /*<<< orphan*/  alloc_pioinfo_block (int) ; 
 int /*<<< orphan*/ * get_ioinfo (int) ; 

__attribute__((used)) static inline ioinfo* get_ioinfo_alloc_fd(int fd)
{
    ioinfo *ret;

    ret = get_ioinfo(fd);
    if(ret != &__badioinfo)
        return ret;

    if(!alloc_pioinfo_block(fd))
        return &__badioinfo;

    return get_ioinfo(fd);
}