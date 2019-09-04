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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TEST_STATUS ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 int GMEM_DISCARDED ; 
 int GMEM_LOCKCOUNT ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GlobalFlags (scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 scalar_t__ GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Handle (scalar_t__) ; 
 int /*<<< orphan*/  OUTPUT_HexDword (int) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 
 int /*<<< orphan*/  SKIPPED ; 
 int /*<<< orphan*/  TEST_CombineStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TEST_STATUS TestGlobalFlagsMoveable()
{
    HGLOBAL     hMem   = 0;
    UINT        uFlags = 0;
    TEST_STATUS result = SKIPPED;

    OUTPUT_Line("Test for the proper lock count");

    hMem = GlobalAlloc(GMEM_MOVEABLE, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {

        OUTPUT_Line("Testing initial allocation");

        OUTPUT_Line("Testing for a lock of 0");
        uFlags = GlobalFlags(hMem);
        if (((GMEM_LOCKCOUNT & uFlags) == 0)) /*no locks*/
        {
            result = TEST_CombineStatus(result, PASSED);
        }
        else
        {
            result = TEST_CombineStatus(result, FAILED);
        }
        OUTPUT_Result(result);

        OUTPUT_Line("Pointer from handle: ");
        OUTPUT_Handle(GlobalLock(hMem));

        OUTPUT_Line("Testing after a lock");
        OUTPUT_Line("Testing for a lock of 1");
        uFlags = GlobalFlags(hMem);
        if (((GMEM_LOCKCOUNT & uFlags) == 1)) /*no locks*/
        {
            result = TEST_CombineStatus(result, PASSED);
        }
        else
        {
            result = TEST_CombineStatus(result, FAILED);
        }
        OUTPUT_Result(result);

        GlobalUnlock(hMem);
        OUTPUT_Line("Testing after an unlock");
        OUTPUT_Line("Testing for a lock of 0");
        uFlags = GlobalFlags(hMem);
        if (((GMEM_LOCKCOUNT & uFlags) == 0)) /*no locks*/
        {
            result = TEST_CombineStatus(result, PASSED);
        }
        else
        {
            result = TEST_CombineStatus(result, FAILED);
        }
        OUTPUT_Result(result);
    }
    else
    {
        OUTPUT_Line("GlobalAlloc failed!");
        result = TEST_CombineStatus(result, FAILED);
    }

    OUTPUT_Line("Test for discarded memory");
    OUTPUT_Line("Allocating an empty moveable block---automatically marked as discarded");
    hMem = GlobalAlloc(GMEM_MOVEABLE, 0); /*allocate a discarded block*/
    if (0 != hMem)
    {
        OUTPUT_Line("Allocation handle: ");
        OUTPUT_Handle(hMem);
        OUTPUT_Line("Testing for a discarded flag");
        uFlags = GlobalFlags(hMem);
        if (0 != (uFlags & GMEM_DISCARDED)) /*discarded*/
        {
            result = TEST_CombineStatus(result, PASSED);
        }
        else
        {
            result = TEST_CombineStatus(result, FAILED);
        }
        OUTPUT_Line("Flags:");
        OUTPUT_HexDword(uFlags);
        OUTPUT_Result(result);

        GlobalFree(hMem);
    }
    else
    {
        OUTPUT_Line("GlobalAlloc failed!");
        result = TEST_CombineStatus(result, FAILED);
    }
    return result;
}