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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IsBadReadPtr (char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_IsBadReadPtr(void)
{
    BOOL ret;
    void *ptr = (void *)0xdeadbeef;
    char stackvar;

    ret = IsBadReadPtr(NULL, 0);
    ok(ret == FALSE, "Expected IsBadReadPtr to return FALSE, got %d\n", ret);

    ret = IsBadReadPtr(NULL, 1);
    ok(ret == TRUE, "Expected IsBadReadPtr to return TRUE, got %d\n", ret);

    ret = IsBadReadPtr(ptr, 0);
    ok(ret == FALSE, "Expected IsBadReadPtr to return FALSE, got %d\n", ret);

    ret = IsBadReadPtr(ptr, 1);
    ok(ret == TRUE, "Expected IsBadReadPtr to return TRUE, got %d\n", ret);

    ret = IsBadReadPtr(&stackvar, 0);
    ok(ret == FALSE, "Expected IsBadReadPtr to return FALSE, got %d\n", ret);

    ret = IsBadReadPtr(&stackvar, sizeof(char));
    ok(ret == FALSE, "Expected IsBadReadPtr to return FALSE, got %d\n", ret);
}