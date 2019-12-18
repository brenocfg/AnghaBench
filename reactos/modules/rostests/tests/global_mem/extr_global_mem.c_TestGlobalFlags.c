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

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_Banner (char*) ; 
 int /*<<< orphan*/  OUTPUT_Line (char*) ; 
 int /*<<< orphan*/  OUTPUT_Result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKIPPED ; 
 int /*<<< orphan*/  TEST_CombineStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestGlobalFlagsFixed () ; 
 int /*<<< orphan*/  TestGlobalFlagsMoveable () ; 

TEST_STATUS TestGlobalFlags()
{
    TEST_STATUS result = SKIPPED;
    OUTPUT_Banner("Testing GlobalFlags()");

    result = TEST_CombineStatus(result, TestGlobalFlagsFixed());
    result = TEST_CombineStatus(result, TestGlobalFlagsMoveable());

    OUTPUT_Line("GlobalFlags result:");
    OUTPUT_Result(result);
    return result;
}