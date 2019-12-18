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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetActiveProcessorCount (int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetActiveProcessorCount(void)
{
    DWORD count;

    if (!pGetActiveProcessorCount)
    {
        win_skip("GetActiveProcessorCount not available, skipping test\n");
        return;
    }

    count = pGetActiveProcessorCount(0);
    ok(count, "GetActiveProcessorCount failed, error %u\n", GetLastError());

    /* Test would fail on systems with more than 6400 processors */
    SetLastError(0xdeadbeef);
    count = pGetActiveProcessorCount(101);
    ok(count == 0, "Expeced GetActiveProcessorCount to fail\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());
}