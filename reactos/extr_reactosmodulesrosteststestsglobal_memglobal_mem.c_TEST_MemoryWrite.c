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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED ; 
 scalar_t__ IsBadWritePtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PASSED ; 

TEST_STATUS TEST_MemoryWrite(LPVOID mem, DWORD cbSize)
{
    TEST_STATUS result = FAILED;

    if (0 == IsBadWritePtr(mem, cbSize))
    {
        result = PASSED;
    }
    return result;
}