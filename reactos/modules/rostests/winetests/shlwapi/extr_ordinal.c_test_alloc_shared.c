#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct shared_struct {int value; int /*<<< orphan*/ * handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetCurrentProcessId () ; 
 int GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pSHAllocShared (struct shared_struct*,int,int) ; 
 int pSHFreeShared (int /*<<< orphan*/ *,int) ; 
 struct shared_struct* pSHLockShared (int /*<<< orphan*/ *,int) ; 
 int pSHUnlockShared (struct shared_struct*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_alloc_shared(int argc, char **argv)
{
    char cmdline[MAX_PATH];
    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { 0 };
    DWORD procid;
    HANDLE hmem, hmem2 = 0;
    struct shared_struct val, *p;
    BOOL ret;

    procid=GetCurrentProcessId();
    hmem=pSHAllocShared(NULL,10,procid);
    ok(hmem!=NULL,"SHAllocShared(NULL...) failed: %u\n", GetLastError());
    ret = pSHFreeShared(hmem, procid);
    ok( ret, "SHFreeShared failed: %u\n", GetLastError());

    val.value = 0x12345678;
    val.handle = 0;
    hmem = pSHAllocShared(&val, sizeof(val), procid);
    ok(hmem!=NULL,"SHAllocShared(NULL...) failed: %u\n", GetLastError());

    p=pSHLockShared(hmem,procid);
    ok(p!=NULL,"SHLockShared failed: %u\n", GetLastError());
    if (p!=NULL)
        ok(p->value == 0x12345678, "Wrong value in shared memory: %d instead of %d\n", p->value, 0x12345678);
    ret = pSHUnlockShared(p);
    ok( ret, "SHUnlockShared failed: %u\n", GetLastError());

    sprintf(cmdline, "%s %s %d %p", argv[0], argv[1], procid, hmem);
    ret = CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    ok(ret, "could not create child process error: %u\n", GetLastError());
    if (ret)
    {
        winetest_wait_child_process(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

        p = pSHLockShared(hmem, procid);
        ok(p != NULL,"SHLockShared failed: %u\n", GetLastError());
        if (p != NULL && p->value != 0x12345678)
        {
            ok(p->value == 0x12345679, "Wrong value in shared memory: %d instead of %d\n", p->value, 0x12345679);
            hmem2 = p->handle;
            ok(hmem2 != NULL, "Expected handle in shared memory\n");
        }
        ret = pSHUnlockShared(p);
        ok(ret, "SHUnlockShared failed: %u\n", GetLastError());
    }

    ret = pSHFreeShared(hmem, procid);
    ok( ret, "SHFreeShared failed: %u\n", GetLastError());

    if (hmem2)
    {
        p = pSHLockShared(hmem2, procid);
        ok(p != NULL,"SHLockShared failed: %u\n", GetLastError());
        if (p != NULL)
            ok(p->value == 0xDEADBEEF, "Wrong value in shared memory: %d instead of %d\n", p->value, 0xDEADBEEF);
        ret = pSHUnlockShared(p);
        ok(ret, "SHUnlockShared failed: %u\n", GetLastError());

        ret = pSHFreeShared(hmem2, procid);
        ok(ret, "SHFreeShared failed: %u\n", GetLastError());
    }

    SetLastError(0xdeadbeef);
    ret = pSHFreeShared(NULL, procid);
    ok(ret, "SHFreeShared failed: %u\n", GetLastError());
    ok(GetLastError() == 0xdeadbeef, "last error should not have changed, got %u\n", GetLastError());
}