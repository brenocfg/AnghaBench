#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  funcs ;
struct TYPE_3__ {int cbStruct; int /*<<< orphan*/ * pfnFree; int /*<<< orphan*/ * pfnAlloc; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_1__ CRYPT_PROVIDER_FUNCTIONS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WINTRUST_ACTION_GENERIC_VERIFY_V2 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pWintrustLoadFunctionPointers (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LoadFunctionPointers(void)
{
    BOOL ret;
    CRYPT_PROVIDER_FUNCTIONS funcs = {0};
    GUID action = WINTRUST_ACTION_GENERIC_VERIFY_V2;

    if (!pWintrustLoadFunctionPointers)
    {
        win_skip("WintrustLoadFunctionPointers is not available\n");
        return;
    }
    SetLastError(0xdeadbeef);
    ret = pWintrustLoadFunctionPointers(NULL, NULL);
    ok(!ret && GetLastError() == 0xdeadbeef, "Expected failure\n");
    SetLastError(0xdeadbeef);
    ret = pWintrustLoadFunctionPointers(&action, NULL);
    ok(!ret && GetLastError() == 0xdeadbeef, "Expected failure\n");

    SetLastError(0xdeadbeef);
    ret = pWintrustLoadFunctionPointers(NULL, &funcs);
    ok(!ret, "WintrustLoadFunctionPointers succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
        GetLastError() == 0xdeadbeef /* W2K and XP-SP1 */,
        "Expected ERROR_INVALID_PARAMETER or 0xdeadbeef, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    funcs.cbStruct = 0;
    ret = pWintrustLoadFunctionPointers(&action, &funcs);
    ok(!ret && GetLastError() == 0xdeadbeef, "Expected failure\n");
    SetLastError(0xdeadbeef);
    funcs.cbStruct = sizeof(funcs);
    ret = pWintrustLoadFunctionPointers(&action, &funcs);
    ok(ret, "WintrustLoadFunctionPointers failed: %d\n", GetLastError());
    ok(funcs.pfnAlloc != NULL, "Expected a pointer\n");
    ok(funcs.pfnFree != NULL, "Expected a pointer\n");
}