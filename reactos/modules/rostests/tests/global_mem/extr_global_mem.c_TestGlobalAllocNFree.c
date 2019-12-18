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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  TEST_STATUS ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GlobalFree (scalar_t__) ; 
 int /*<<< orphan*/  MEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OUTPUT_Banner (char*) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutputAllocFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 
 int /*<<< orphan*/  SKIPPED ; 

TEST_STATUS TestGlobalAllocNFree(UINT allocFlags)
{
    TEST_STATUS status = SKIPPED;
    HGLOBAL hTest = 0;
    OUTPUT_Banner("Testing the GlobalAlloc and GlobalFree calls");
    OUTPUT_Line("Allocate a buffer");

    OutputAllocFlags(allocFlags);

    status = FAILED;
    hTest = GlobalAlloc(allocFlags, MEM_BLOCK_SIZE);
    if (0 != hTest)
    {
        if (0 == GlobalFree(hTest))
        {
            status = PASSED;
        }
    }

    OUTPUT_Line("Result for this run:");
    OUTPUT_Result(status);
    OUTPUT_Line("");

    return status;
}