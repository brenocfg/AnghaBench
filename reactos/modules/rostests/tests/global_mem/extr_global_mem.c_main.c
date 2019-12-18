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

/* Variables and functions */
 scalar_t__ FAILED ; 
 int /*<<< orphan*/  GHND ; 
 int /*<<< orphan*/  GMEM_FIXED ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GPTR ; 
 int /*<<< orphan*/  OUTPUT_Banner (char*) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (scalar_t__) ; 
 scalar_t__ SKIPPED ; 
 scalar_t__ TEST_CombineStatus (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestGlobalAllocNFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestGlobalDiscard () ; 
 int /*<<< orphan*/  TestGlobalFlags () ; 
 int /*<<< orphan*/  TestGlobalHandle () ; 
 int /*<<< orphan*/  TestGlobalLockNUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestGlobalReAlloc () ; 
 int /*<<< orphan*/  TestGlobalSize () ; 

int main(int argc, char ** argv)
{
    TEST_STATUS test_set = SKIPPED;
    OUTPUT_Banner("Testing GlobalXXX memory management functions.");

    test_set = TEST_CombineStatus(test_set, TestGlobalAllocNFree(GPTR));
    test_set = TEST_CombineStatus(test_set, TestGlobalAllocNFree(GHND));
    test_set = TEST_CombineStatus(test_set, TestGlobalAllocNFree(GMEM_FIXED));
    test_set = TEST_CombineStatus(test_set, TestGlobalAllocNFree(GMEM_MOVEABLE));

    if (FAILED == test_set)
    {
        OUTPUT_Line("Skipping any further tests.  GlobalAlloc/Free fails.");
        OUTPUT_Result(test_set);
        return test_set;
    }

    test_set = TEST_CombineStatus(test_set, TestGlobalLockNUnlock(GPTR));
    test_set = TEST_CombineStatus(test_set, TestGlobalLockNUnlock(GHND));
    test_set = TEST_CombineStatus(test_set, TestGlobalLockNUnlock(GMEM_FIXED));
    test_set = TEST_CombineStatus(test_set, TestGlobalLockNUnlock(GMEM_MOVEABLE));

    test_set = TEST_CombineStatus(test_set, TestGlobalReAlloc());

    test_set = TEST_CombineStatus(test_set, TestGlobalFlags());

    test_set = TEST_CombineStatus(test_set, TestGlobalHandle());

    test_set = TEST_CombineStatus(test_set, TestGlobalSize());

    test_set = TEST_CombineStatus(test_set, TestGlobalDiscard());

    /* output the result for the entire set of tests*/
    OUTPUT_Banner("Test suite result");
    OUTPUT_Result(test_set);
    return test_set;
}