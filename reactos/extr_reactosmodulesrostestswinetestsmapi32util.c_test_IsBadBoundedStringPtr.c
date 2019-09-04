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

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pIsBadBoundedStringPtr (char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_IsBadBoundedStringPtr(void)
{
    if (!pIsBadBoundedStringPtr)
    {
        win_skip("IsBadBoundedStringPtr is not available\n");
        return;
    }

    ok(pIsBadBoundedStringPtr(NULL, 0) == TRUE, "IsBadBoundedStringPtr: expected TRUE\n");
    ok(pIsBadBoundedStringPtr("TEST", 4) == TRUE, "IsBadBoundedStringPtr: expected TRUE\n");
    ok(pIsBadBoundedStringPtr("TEST", 5) == FALSE, "IsBadBoundedStringPtr: expected FALSE\n");
}