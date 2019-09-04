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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HCRYPTMSG ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_E_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  CryptMsgGetParam (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OSS_LIMITED ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  win_skip (char*,int) ; 

__attribute__((used)) static void check_param(LPCSTR test, HCRYPTMSG msg, DWORD param,
 const BYTE *expected, DWORD expectedSize)
{
    DWORD size;
    LPBYTE buf;
    BOOL ret;

    size = 0xdeadbeef;
    ret = CryptMsgGetParam(msg, param, 0, NULL, &size);
    ok(ret || broken(GetLastError() == OSS_LIMITED /* Win9x */ ||
     GetLastError() == CRYPT_E_INVALID_MSG_TYPE /* Win9x, for some params */),
     "%s: CryptMsgGetParam failed: %08x\n", test, GetLastError());
    if (!ret)
    {
        win_skip("parameter %d not supported, skipping tests\n", param);
        return;
    }
    buf = HeapAlloc(GetProcessHeap(), 0, size);
    ret = CryptMsgGetParam(msg, param, 0, buf, &size);
    ok(ret, "%s: CryptMsgGetParam failed: %08x\n", test, GetLastError());
    ok(size == expectedSize, "%s: expected size %d, got %d\n", test,
     expectedSize, size);
    if (size == expectedSize && size)
        ok(!memcmp(buf, expected, size), "%s: unexpected data\n", test);
    HeapFree(GetProcessHeap(), 0, buf);
}