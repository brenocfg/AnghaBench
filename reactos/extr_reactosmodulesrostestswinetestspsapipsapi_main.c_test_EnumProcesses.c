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
typedef  int DWORD ;

/* Variables and functions */
 int EnumProcesses (int*,int,int*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_EnumProcesses(void)
{
    DWORD pid, ret, cbUsed = 0xdeadbeef;

    SetLastError(0xdeadbeef);
    ret = EnumProcesses(NULL, 0, &cbUsed);
    ok(ret == 1, "failed with %d\n", GetLastError());
    ok(cbUsed == 0, "cbUsed=%d\n", cbUsed);

    SetLastError(0xdeadbeef);
    ret = EnumProcesses(&pid, 4, &cbUsed);
    ok(ret == 1, "failed with %d\n", GetLastError());
    ok(cbUsed == 4, "cbUsed=%d\n", cbUsed);
}