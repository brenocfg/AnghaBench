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
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 int /*<<< orphan*/  GMEM_FIXED ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 scalar_t__ GlobalSize (scalar_t__) ; 
 scalar_t__ MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Banner (char*) ; 
 int /*<<< orphan*/  OUTPUT_HexDword (scalar_t__) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 
 int /*<<< orphan*/  SKIPPED ; 
 int /*<<< orphan*/  TEST_CombineStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TEST_STATUS TestGlobalSize()
{
    HGLOBAL hMem = 0;
    SIZE_T  size = 0;
    TEST_STATUS subtest = SKIPPED;
    TEST_STATUS result  = SKIPPED;
    OUTPUT_Banner("Testing GlobalSize()");

    OUTPUT_Line("Testing GlobalSize with a block of GMEM_FIXED memory");
    hMem = GlobalAlloc(GMEM_FIXED, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {
        size = GlobalSize(hMem);
        if (MEM_BLOCK_SIZE <= size)
        {
            subtest = TEST_CombineStatus(subtest, PASSED);
        }
        else
        {
            OUTPUT_Line("GlobalSize returned:");
            OUTPUT_HexDword(size);
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

    OUTPUT_Line("Testing GlobalSize with a block of GMEM_MOVEABLE memory");
    hMem = GlobalAlloc(GMEM_MOVEABLE, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {
        size = GlobalSize(hMem);
        if (MEM_BLOCK_SIZE <= size)
        {
            subtest = TEST_CombineStatus(subtest, PASSED);
        }
        else
        {
            OUTPUT_Line("GlobalSize returned:");
            OUTPUT_HexDword(size);
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

    OUTPUT_Line("Testing GlobalSize with discarded memory");
    hMem = GlobalAlloc(GMEM_MOVEABLE, 0);
    if (0 != hMem)
    {
        size = GlobalSize(hMem);
        if (0 == size)
        {
            subtest = TEST_CombineStatus(subtest, PASSED);
        }
        else
        {
            OUTPUT_Line("GlobalSize returned:");
            OUTPUT_HexDword(size);
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

    OUTPUT_Line("Test result:");
    OUTPUT_Result(result);
    return result;
}