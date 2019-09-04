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
typedef  int /*<<< orphan*/  TEST_STATUS ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 int /*<<< orphan*/  GMEM_FIXED ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 scalar_t__ GlobalHandle (scalar_t__) ; 
 scalar_t__ GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Banner (char*) ; 
 int /*<<< orphan*/  OUTPUT_Handle (scalar_t__) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 
 int /*<<< orphan*/  SKIPPED ; 
 int /*<<< orphan*/  TEST_CombineStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TEST_STATUS TestGlobalHandle()
{
    HGLOBAL     hMem    = 0;
    HGLOBAL     hTest   = 0;
    PVOID       pMem    = 0;
    TEST_STATUS subtest = SKIPPED;
    TEST_STATUS result  = SKIPPED;

    OUTPUT_Banner("Testing GlobalHandle()");

    OUTPUT_Line("Testing GlobalHandle with a block of GMEM_FIXED memory");
    hMem = GlobalAlloc(GMEM_FIXED, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {

        OUTPUT_Line("Allocation handle: ");
        OUTPUT_Handle(hMem);

        hTest = GlobalHandle(hMem);
        if (hMem == hTest)
        {
            subtest = TEST_CombineStatus(subtest, PASSED);
        }
        else
        {
            OUTPUT_Line("GlobalHandle returned:");
            OUTPUT_Handle(hTest);
            subtest = TEST_CombineStatus(subtest, FAILED);
        }

        GlobalFree(hMem);
    }
    else
    {
        OUTPUT_Line("GlobalAlloc failed!");
        subtest = TEST_CombineStatus(subtest, FAILED);
    }

    OUTPUT_Line("Result from subtest:");
    OUTPUT_Result(subtest);
    result = TEST_CombineStatus(result, subtest);


    subtest = SKIPPED;
    OUTPUT_Line("Testing GlobalHandle with a block of GMEM_MOVEABLE memory");
    hMem = GlobalAlloc(GMEM_MOVEABLE, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {

        OUTPUT_Line("Allocation handle: ");
        OUTPUT_Handle(hMem);
        pMem = GlobalLock(hMem);
        hTest = GlobalHandle(pMem);
        if (hMem == hTest)
        {
            subtest = TEST_CombineStatus(subtest, PASSED);
        }
        else
        {
            OUTPUT_Line("GlobalHandle returned:");
            OUTPUT_Handle(hTest);
            subtest = TEST_CombineStatus(subtest, FAILED);
        }

        GlobalUnlock(hMem);
        GlobalFree(hMem);
    }
    else
    {
        OUTPUT_Line("GlobalAlloc failed!");
        subtest = TEST_CombineStatus(subtest, FAILED);
    }

    OUTPUT_Line("Result from subtest:");
    OUTPUT_Result(subtest);
    result = TEST_CombineStatus(result, subtest);


    OUTPUT_Line("Global Handle test results:");
    OUTPUT_Result(result);
    return result;
}