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
struct TYPE_6__ {scalar_t__ handle; int /*<<< orphan*/  crit; } ;
typedef  TYPE_1__ ioinfo ;

/* Variables and functions */
 int /*<<< orphan*/  ENFILE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MSVCRT_MAX_FILES ; 
 scalar_t__ TryEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 TYPE_1__ __badioinfo ; 
 int /*<<< orphan*/ * _errno () ; 
 int /*<<< orphan*/  alloc_pioinfo_block (int) ; 
 TYPE_1__* get_ioinfo_nolock (int) ; 
 int /*<<< orphan*/  init_ioinfo_cs (TYPE_1__*) ; 

__attribute__((used)) static inline ioinfo* get_ioinfo_alloc(int *fd)
{
    int i;

    *fd = -1;
    for(i=0; i<MSVCRT_MAX_FILES; i++)
    {
        ioinfo *info = get_ioinfo_nolock(i);

        if(info == &__badioinfo)
        {
            if(!alloc_pioinfo_block(i))
                return &__badioinfo;
            info = get_ioinfo_nolock(i);
        }

        init_ioinfo_cs(info);
        if(TryEnterCriticalSection(&info->crit))
        {
            if(info->handle == INVALID_HANDLE_VALUE)
            {
                *fd = i;
                return info;
            }
            LeaveCriticalSection(&info->crit);
        }
    }

    WARN(":files exhausted!\n");
    *_errno() = ENFILE;
    return &__badioinfo;
}