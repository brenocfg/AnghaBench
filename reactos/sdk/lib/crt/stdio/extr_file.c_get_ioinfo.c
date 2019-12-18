#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  crit; } ;
typedef  TYPE_1__ ioinfo ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__ __badioinfo ; 
 TYPE_1__* get_ioinfo_nolock (int) ; 
 int /*<<< orphan*/  init_ioinfo_cs (TYPE_1__*) ; 

ioinfo* get_ioinfo(int fd)
{
    ioinfo *ret = get_ioinfo_nolock(fd);
    if(ret == &__badioinfo)
        return ret;
    init_ioinfo_cs(ret);
    EnterCriticalSection(&ret->crit);
    return ret;
}