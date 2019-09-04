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
 int /*<<< orphan*/  GMEM_FIXED ; 
 int GMEM_LOCKCOUNT ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GlobalFlags (scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 scalar_t__ GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Handle (scalar_t__) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 
 int /*<<< orphan*/  SKIPPED ; 
 int /*<<< orphan*/  TEST_CombineStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TEST_STATUS TestGlobalFlagsFixed()
{
    HGLOBAL     hMem   = 0;
    UINT        uFlags = 0;
    TEST_STATUS result = SKIPPED;

    OUTPUT_Line("Testing for correct handling of GMEM_FIXED memory");
    hMem = GlobalAlloc(GMEM_FIXED, MEM_BLOCK_SIZE);
    if (0 != hMem)
    {

        OUTPUT_Line("Allocation handle: ");
        OUTPUT_Handle(hMem);

        OUTPUT_Line("Testing initial allocation");
        OUTPUT_Line("Testing for non-discarded and lock of 0");
        uFlags = GlobalFlags(hMem);
        if (((GMEM_LOCKCOUNT & uFlags) == 0) && /*no locks*/
            (((uFlags >> 8) & 0xff) == 0 ))   /*not discarded*/
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
        OUTPUT_Line("Testing for non-discarded and lock of 0");
        uFlags = GlobalFlags(hMem);
        if (((GMEM_LOCKCOUNT & uFlags) == 0) && /*no locks*/
            (((uFlags >> 8) & 0xff) == 0 ))   /*not discarded*/
        {
            result = TEST_CombineStatus(result, PASSED);
        }
        else
        {
            result = TEST_CombineStatus(result, FAILED);
        }
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