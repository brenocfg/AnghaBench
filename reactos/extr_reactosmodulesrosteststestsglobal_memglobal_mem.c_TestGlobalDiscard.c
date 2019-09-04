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
typedef  scalar_t__ HGLOBAL ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 int GMEM_DISCARDED ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GlobalDiscard (scalar_t__) ; 
 int GlobalFlags (scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 int /*<<< orphan*/  MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Banner (char*) ; 
 int /*<<< orphan*/  OUTPUT_Handle (scalar_t__) ; 
 int /*<<< orphan*/  OUTPUT_HexDword (int) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 
 int /*<<< orphan*/  SKIPPED ; 
 int /*<<< orphan*/  TEST_CombineStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TEST_STATUS TestGlobalDiscard()
{
    HGLOBAL     hMem    = 0;
    HGLOBAL     hTest   = 0;
    DWORD       uFlags  = 0;
    TEST_STATUS subtest = SKIPPED;
    TEST_STATUS result  = SKIPPED;

    OUTPUT_Banner("Testing GlobalDiscard()");
    hMem = GlobalAlloc(GMEM_MOVEABLE, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {
        OUTPUT_Line("Allocation handle: ");
        OUTPUT_Handle(hMem);

        hTest = GlobalDiscard(hMem);
        if (0 == hTest)
        {
            OUTPUT_Line("GlobalDiscard returned NULL");
            subtest = TEST_CombineStatus(subtest, FAILED);
        }
        else
        {
            uFlags = GlobalFlags(hTest);
            OUTPUT_Line("Flags from the new memory block.");
            OUTPUT_HexDword(uFlags);
            if (0 != (uFlags & GMEM_DISCARDED))
            {
                subtest = TEST_CombineStatus(subtest, PASSED);
            }
            else
            {
                OUTPUT_Line("Block is not marked as discardable.");
                subtest = TEST_CombineStatus(subtest, FAILED);
            }
        }

        GlobalFree(hTest);
    }
    else
    {
        OUTPUT_Line("GlobalAlloc failed!");
        subtest = TEST_CombineStatus(subtest, FAILED);
    }

    OUTPUT_Line("Result from subtest:");
    OUTPUT_Result(subtest);

    result = TEST_CombineStatus(result, subtest);

    OUTPUT_Result(result);
    return result;
}