#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ioinfo ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ENFILE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int MSVCRT_FD_BLOCK_SIZE ; 
 int MSVCRT_MAX_FILES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * __pioinfo ; 
 int /*<<< orphan*/ * _errno () ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static inline BOOL alloc_pioinfo_block(int fd)
{
    ioinfo *block;
    int i;

    if(fd<0 || fd>=MSVCRT_MAX_FILES)
    {
        *_errno() = ENFILE;
        return FALSE;
    }

    block = calloc(MSVCRT_FD_BLOCK_SIZE, sizeof(ioinfo));
    if(!block)
    {
        WARN(":out of memory!\n");
        *_errno() = ENOMEM;
        return FALSE;
    }
    for(i=0; i<MSVCRT_FD_BLOCK_SIZE; i++)
        block[i].handle = INVALID_HANDLE_VALUE;
    if(InterlockedCompareExchangePointer((void**)&__pioinfo[fd/MSVCRT_FD_BLOCK_SIZE], block, NULL))
        free(block);
    return TRUE;
}