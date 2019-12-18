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
typedef  int TEST_STATUS ;

/* Variables and functions */
#define  FAILED 130 
#define  PASSED 129 
#define  SKIPPED 128 

TEST_STATUS TEST_CombineStatus(TEST_STATUS a, TEST_STATUS b)
{
    TEST_STATUS result = a;

    switch (a)
    {
    case PASSED:  result = (PASSED == b || SKIPPED == b) ? (PASSED) : (FAILED); break;
    case FAILED:  result = FAILED; break;
    case SKIPPED: result = b; break;
    }

    return result;
}