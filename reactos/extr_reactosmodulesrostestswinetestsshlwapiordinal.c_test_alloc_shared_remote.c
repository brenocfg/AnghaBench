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
typedef  int /*<<< orphan*/  val ;
struct shared_struct {int value; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pSHAllocShared (struct shared_struct*,int,int /*<<< orphan*/ ) ; 
 int pSHFreeShared (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct shared_struct* pSHLockShared (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pSHMapHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pSHUnlockShared (struct shared_struct*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_alloc_shared_remote(DWORD procid, HANDLE hmem)
{
    struct shared_struct val, *p;
    HANDLE hmem2;
    BOOL ret;

    /* test directly accessing shared memory of a remote process */
    p = pSHLockShared(hmem, procid);
    ok(p != NULL || broken(p == NULL) /* Windows 7/8 */, "SHLockShared failed: %u\n", GetLastError());
    if (p == NULL)
    {
        win_skip("Subprocess failed to modify shared memory, skipping test\n");
        return;
    }

    ok(p->value == 0x12345678, "Wrong value in shared memory: %d instead of %d\n", p->value, 0x12345678);
    p->value++;

    val.value = 0xDEADBEEF;
    val.handle = 0;
    p->handle = pSHAllocShared(&val, sizeof(val), procid);
    ok(p->handle != NULL, "SHAllocShared failed: %u\n", GetLastError());

    ret = pSHUnlockShared(p);
    ok(ret, "SHUnlockShared failed: %u\n", GetLastError());

    /* test SHMapHandle */
    SetLastError(0xdeadbeef);
    hmem2 = pSHMapHandle(NULL, procid, GetCurrentProcessId(), 0, 0);
    ok(hmem2 == NULL, "expected NULL, got new handle\n");
    ok(GetLastError() == 0xdeadbeef, "last error should not have changed, got %u\n", GetLastError());

    hmem2 = pSHMapHandle(hmem, procid, GetCurrentProcessId(), 0, 0);

    /* It seems like Windows Vista/2008 uses a different internal implementation
     * for shared memory, and calling SHMapHandle fails. */
    ok(hmem2 != NULL || broken(hmem2 == NULL),
       "SHMapHandle failed: %u\n", GetLastError());
    if (hmem2 == NULL)
    {
        win_skip("Subprocess failed to map shared memory, skipping test\n");
        return;
    }

    p = pSHLockShared(hmem2, GetCurrentProcessId());
    ok(p != NULL, "SHLockShared failed: %u\n", GetLastError());

    if (p != NULL)
        ok(p->value == 0x12345679, "Wrong value in shared memory: %d instead of %d\n", p->value, 0x12345679);

    ret = pSHUnlockShared(p);
    ok(ret, "SHUnlockShared failed: %u\n", GetLastError());

    ret = pSHFreeShared(hmem2, GetCurrentProcessId());
    ok(ret, "SHFreeShared failed: %u\n", GetLastError());
}