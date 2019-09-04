#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* DebugInfo; } ;
struct chmFile {TYPE_2__ cache_mutex; TYPE_2__ lzx_mutex; TYPE_2__ mutex; scalar_t__ cache_num_blocks; int /*<<< orphan*/ * cache_block_indices; int /*<<< orphan*/ * cache_blocks; int /*<<< orphan*/ * lzx_state; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {void** Spare; } ;
typedef  void* DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_MAX_BLOCKS_CACHED ; 
 int /*<<< orphan*/  CHM_PARAM_MAX_BLOCKS_CACHED ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct chmFile* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_2__*) ; 
 int /*<<< orphan*/  chm_set_param (struct chmFile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct chmFile *chm_dup(struct chmFile *oldHandle)
{
    struct chmFile *newHandle=NULL;

    newHandle = HeapAlloc(GetProcessHeap(), 0, sizeof(struct chmFile));
    *newHandle = *oldHandle;

    /* duplicate fd handle */
    DuplicateHandle(GetCurrentProcess(), oldHandle->fd,
                    GetCurrentProcess(), &(newHandle->fd),
                    0, FALSE, DUPLICATE_SAME_ACCESS);
    newHandle->lzx_state = NULL;
    newHandle->cache_blocks = NULL;
    newHandle->cache_block_indices = NULL;
    newHandle->cache_num_blocks = 0;

    /* initialize mutexes, if needed */
    InitializeCriticalSection(&newHandle->mutex);
    newHandle->mutex.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": chmFile.mutex");
    InitializeCriticalSection(&newHandle->lzx_mutex);
    newHandle->lzx_mutex.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": chmFile.lzx_mutex");
    InitializeCriticalSection(&newHandle->cache_mutex);
    newHandle->cache_mutex.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": chmFile.cache_mutex");

    /* initialize cache */
    chm_set_param(newHandle, CHM_PARAM_MAX_BLOCKS_CACHED,
                  CHM_MAX_BLOCKS_CACHED);

    return newHandle;
}