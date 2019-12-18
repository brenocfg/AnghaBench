#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  he ;
struct TYPE_7__ {int dwSize; scalar_t__ dwAddress; scalar_t__ dwBlockSize; } ;
struct TYPE_6__ {int wFlags; int /*<<< orphan*/ * lpData; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__ PROCESS_HEAP_ENTRY ;
typedef  TYPE_2__ HEAPENTRY32 ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 scalar_t__ Heap32First (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Heap32Next (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapLock (scalar_t__) ; 
 int /*<<< orphan*/  HeapUnlock (scalar_t__) ; 
 scalar_t__ HeapWalk (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int PROCESS_HEAP_ENTRY_BUSY ; 
 int /*<<< orphan*/  TH32CS_SNAPHEAPLIST ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static BOOL IsBlockFromHeap(HANDLE hHeap, PVOID ptr)
{
    /* Use when this is implemented */
#if 0
    PROCESS_HEAP_ENTRY Entry;
    BOOL ret = FALSE;
    if (!HeapLock(hHeap))
    {
        skip("Unable to lock heap\n");
        return FALSE;
    }

    Entry.lpData = NULL;
    while (!ret && HeapWalk(hHeap, &Entry))
    {
        if ((Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) &&
            (Entry.lpData == ptr))
        {
            ret = TRUE;
        }
    }

    HeapUnlock(hHeap);
    return ret;
#else
    HEAPENTRY32 he;
    BOOL ret = FALSE;
    HANDLE hHeapSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, GetCurrentProcessId());

    if (hHeapSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    he.dwSize = sizeof(he);

    if (Heap32First(&he, GetCurrentProcessId(), (DWORD_PTR)hHeap))
    {
        do {
            if ((DWORD_PTR)ptr >= he.dwAddress && (DWORD_PTR)ptr <= (he.dwAddress + he.dwBlockSize))
                ret = TRUE;
        } while (!ret && Heap32Next(&he));
    }

    CloseHandle(hHeapSnap);

    return ret;
#endif
}