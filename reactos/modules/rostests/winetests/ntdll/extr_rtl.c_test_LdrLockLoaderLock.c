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
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int NTSTATUS ;

/* Variables and functions */
 int STATUS_INVALID_PARAMETER_1 ; 
 int STATUS_INVALID_PARAMETER_2 ; 
 int STATUS_INVALID_PARAMETER_3 ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pLdrLockLoaderLock (int,int*,int*) ; 
 int /*<<< orphan*/  pLdrUnlockLoaderLock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LdrLockLoaderLock(void)
{
    ULONG_PTR magic;
    ULONG result;
    NTSTATUS status;

    if (!pLdrLockLoaderLock)
    {
        win_skip("LdrLockLoaderLock() is not available\n");
        return;
    }

    /* invalid flags */
    result = 10;
    magic = 0xdeadbeef;
    status = pLdrLockLoaderLock(0x10, &result, &magic);
    ok(status == STATUS_INVALID_PARAMETER_1, "got 0x%08x\n", status);
    ok(result == 0, "got %d\n", result);
    ok(magic == 0, "got %lx\n", magic);

    magic = 0xdeadbeef;
    status = pLdrLockLoaderLock(0x10, NULL, &magic);
    ok(status == STATUS_INVALID_PARAMETER_1, "got 0x%08x\n", status);
    ok(magic == 0, "got %lx\n", magic);

    result = 10;
    status = pLdrLockLoaderLock(0x10, &result, NULL);
    ok(status == STATUS_INVALID_PARAMETER_1, "got 0x%08x\n", status);
    ok(result == 0, "got %d\n", result);

    /* non-blocking mode, result is null */
    magic = 0xdeadbeef;
    status = pLdrLockLoaderLock(0x2, NULL, &magic);
    ok(status == STATUS_INVALID_PARAMETER_2, "got 0x%08x\n", status);
    ok(magic == 0, "got %lx\n", magic);

    /* magic pointer is null */
    result = 10;
    status = pLdrLockLoaderLock(0, &result, NULL);
    ok(status == STATUS_INVALID_PARAMETER_3, "got 0x%08x\n", status);
    ok(result == 0, "got %d\n", result);

    /* lock in non-blocking mode */
    result = 0;
    magic = 0;
    status = pLdrLockLoaderLock(0x2, &result, &magic);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);
    ok(result == 1, "got %d\n", result);
    ok(magic != 0, "got %lx\n", magic);
    pLdrUnlockLoaderLock(0, magic);
}