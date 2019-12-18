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
typedef  scalar_t__ TEST_STATUS ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 scalar_t__ FAILED ; 
 int /*<<< orphan*/  GMEM_FIXED ; 
 int GMEM_MODIFY ; 
 int GMEM_MOVEABLE ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 int /*<<< orphan*/  GlobalLock (scalar_t__) ; 
 scalar_t__ GlobalReAlloc (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 scalar_t__ IsMovable (scalar_t__) ; 
 scalar_t__ MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Handle (scalar_t__) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (scalar_t__) ; 
 scalar_t__ PASSED ; 
 scalar_t__ SKIPPED ; 
 scalar_t__ TEST_CombineStatus (scalar_t__,scalar_t__) ; 
 scalar_t__ TEST_MemoryRead (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TEST_MemoryWrite (int /*<<< orphan*/ ,scalar_t__) ; 

TEST_STATUS TestGlobalReAllocFixed()
{
    HGLOBAL     hMem       = 0;
    HGLOBAL     hReAlloced = 0;
    LPVOID      pMem       = 0;
    TEST_STATUS subtest    = SKIPPED;
    TEST_STATUS result     = SKIPPED;

    OUTPUT_Line("Testing GlobalReAlloc() on memory allocated as GMEM_FIXED");

    /* Case 1: convert a fixed block to a movable block. */
    OUTPUT_Line("Allocating buffer");
    hMem = GlobalAlloc(GMEM_FIXED, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {
        OUTPUT_Line("Testing to see if this is converted into a movable block");
        hReAlloced = GlobalReAlloc(hMem, MEM_BLOCK_SIZE + 100, GMEM_MOVEABLE | GMEM_MODIFY);
        if (0 == hReAlloced)
        {
            OUTPUT_Line("GlobalReAlloc failed-- returned NULL");
            subtest = TEST_CombineStatus(subtest, FAILED);
            OUTPUT_Result(subtest);
        }
        else
        {
            hMem = hReAlloced;
            if (0 == IsMovable(hMem))
            {
                OUTPUT_Line("GlobalReAlloc returned a fixed pointer.");
                subtest = TEST_CombineStatus(subtest, FAILED);
                OUTPUT_Result(subtest);
            }
            else
            {
                pMem = GlobalLock(hMem);
                subtest = TEST_CombineStatus(subtest, PASSED);
                subtest = TEST_CombineStatus(subtest, TEST_MemoryRead(pMem, MEM_BLOCK_SIZE + 100));
                if (FAILED == subtest)
                {
                    OUTPUT_Line("Memory Read failed.");
                }
                subtest = TEST_CombineStatus(subtest, TEST_MemoryWrite(pMem, MEM_BLOCK_SIZE + 100));
                if (FAILED == subtest)
                {
                    OUTPUT_Line("Memory Write failed.");
                }
                GlobalUnlock(hMem);
            }
        }

        GlobalFree(hMem);
    }
    else
    {
        OUTPUT_Line("Global Alloc Failed.");
        subtest = TEST_CombineStatus(subtest, FAILED);
    }
    OUTPUT_Line("Subtest result:");
    OUTPUT_Result(subtest);
    OUTPUT_Line("");

    result = TEST_CombineStatus(result, subtest);
    subtest = SKIPPED;

    /* case 2 only move a fixed block */
    OUTPUT_Line("Allocating buffer");
    hMem = GlobalAlloc(GMEM_FIXED, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {
        OUTPUT_Line("Testing to see if a new fixed block is returned.");
        hReAlloced = GlobalReAlloc(hMem, MEM_BLOCK_SIZE - 100, GMEM_MOVEABLE);
        if (0 == hReAlloced)
        {
            OUTPUT_Line("GlobalReAlloc failed-- returned NULL");
            subtest = TEST_CombineStatus(subtest, FAILED);
            OUTPUT_Result(subtest);
        }
        else
        {
            OUTPUT_Line("Alloced Handle: ");
            OUTPUT_Handle(hMem);
            OUTPUT_Line("ReAlloced Handle: ");
            OUTPUT_Handle(hReAlloced);
            if (hMem == hReAlloced)
            {
                OUTPUT_Line("GlobalReAlloc returned the same pointer.  The documentation states that this is wrong, but Windows NT works this way.");
            }

            hMem = hReAlloced;
            subtest = TEST_CombineStatus(subtest, PASSED);
            subtest = TEST_CombineStatus(subtest, TEST_MemoryRead((LPVOID)hMem, MEM_BLOCK_SIZE - 100));
            subtest = TEST_CombineStatus(subtest, TEST_MemoryWrite((LPVOID)hMem, MEM_BLOCK_SIZE - 100));
        }

        GlobalFree(hMem);
    }
    else
    {
        subtest = TEST_CombineStatus(subtest, FAILED);
    }
    OUTPUT_Line("Subtest result:");
    OUTPUT_Result(subtest);
    OUTPUT_Line("");

    result = TEST_CombineStatus(result, subtest);
    subtest = SKIPPED;

    /* Case 3: re-allocate a fixed block in place */
    OUTPUT_Line("Allocating buffer");
    hMem = GlobalAlloc(GMEM_FIXED, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {
        OUTPUT_Line("Testing to see if a fixed pointer is reallocated in place.");
        hReAlloced = GlobalReAlloc(hMem, MEM_BLOCK_SIZE - 100, 0);
        if (0 == hReAlloced)
        {
            OUTPUT_Line("GlobalReAlloc failed-- returned NULL");
            subtest = TEST_CombineStatus(subtest, FAILED);
            OUTPUT_Result(subtest);
        }
        else
        {
            OUTPUT_Line("Alloced Handle: ");
            OUTPUT_Handle(hMem);
            OUTPUT_Line("ReAlloced Handle: ");
            OUTPUT_Handle(hReAlloced);
            if (hMem != hReAlloced)
            {
                OUTPUT_Line("GlobalReAlloc returned a different.");
                subtest = TEST_CombineStatus(subtest, FAILED);
                OUTPUT_Result(subtest);
            }
            else
            {
                subtest = TEST_CombineStatus(subtest, PASSED);
                subtest = TEST_CombineStatus(subtest, TEST_MemoryRead((LPVOID)hMem, MEM_BLOCK_SIZE - 100));
                subtest = TEST_CombineStatus(subtest, TEST_MemoryWrite((LPVOID)hMem, MEM_BLOCK_SIZE - 100));
            }
        }

        GlobalFree(hMem);
    }
    else
    {
        subtest = TEST_CombineStatus(subtest, FAILED);
    }
    OUTPUT_Line("Subtest result:");
    OUTPUT_Result(subtest);
    OUTPUT_Line("");

    result = TEST_CombineStatus(result, subtest);

    OUTPUT_Line("");
    return result;
}