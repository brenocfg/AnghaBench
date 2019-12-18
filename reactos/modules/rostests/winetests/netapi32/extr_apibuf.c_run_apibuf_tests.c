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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pNetApiBufferAllocate (int,int /*<<< orphan*/ **) ; 
 scalar_t__ pNetApiBufferFree (int /*<<< orphan*/ *) ; 
 scalar_t__ pNetApiBufferReallocate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ pNetApiBufferSize (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void run_apibuf_tests(void)
{
    VOID *p;
    DWORD dwSize;
    NET_API_STATUS res;

    /* test normal logic */
    ok(pNetApiBufferAllocate(1024, &p) == NERR_Success,
       "Reserved memory\n");
    ok(pNetApiBufferSize(p, &dwSize) == NERR_Success, "Got size\n");
    ok(dwSize >= 1024, "The size is correct\n");

    ok(pNetApiBufferReallocate(p, 1500, &p) == NERR_Success,
       "Reallocated\n");
    ok(pNetApiBufferSize(p, &dwSize) == NERR_Success, "Got size\n");
    ok(dwSize >= 1500, "The size is correct\n");

    ok(pNetApiBufferFree(p) == NERR_Success, "Freed\n");

    ok(pNetApiBufferSize(NULL, &dwSize) == ERROR_INVALID_PARAMETER, "Error for NULL pointer\n");

    /* border reallocate cases */
    ok(pNetApiBufferReallocate(0, 1500, &p) == NERR_Success, "Reallocate with OldBuffer = NULL failed\n");
    ok(p != NULL, "No memory got allocated\n");
    ok(pNetApiBufferFree(p) == NERR_Success, "NetApiBufferFree failed\n");

    ok(pNetApiBufferAllocate(1024, &p) == NERR_Success, "Memory not reserved\n");
    ok(pNetApiBufferReallocate(p, 0, &p) == NERR_Success, "Not freed\n");
    ok(p == NULL, "Pointer not cleared\n");

    /* 0-length buffer */
    ok(pNetApiBufferAllocate(0, &p) == NERR_Success,
       "Reserved memory\n");
    ok(pNetApiBufferSize(p, &dwSize) == NERR_Success, "Got size\n");
    ok(dwSize < 0xFFFFFFFF, "The size of the 0-length buffer\n");
    ok(pNetApiBufferFree(p) == NERR_Success, "Freed\n");

    /* NULL-Pointer */
    /* NT: ERROR_INVALID_PARAMETER, lasterror is untouched) */
    SetLastError(0xdeadbeef);
    res = pNetApiBufferAllocate(0, NULL);
    ok( (res == ERROR_INVALID_PARAMETER) && (GetLastError() == 0xdeadbeef),
        "returned %d with 0x%x (expected ERROR_INVALID_PARAMETER with "
        "0xdeadbeef)\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    res = pNetApiBufferAllocate(1024, NULL);
    ok( (res == ERROR_INVALID_PARAMETER) && (GetLastError() == 0xdeadbeef),
        "returned %d with 0x%x (expected ERROR_INVALID_PARAMETER with "
        "0xdeadbeef)\n", res, GetLastError());
}