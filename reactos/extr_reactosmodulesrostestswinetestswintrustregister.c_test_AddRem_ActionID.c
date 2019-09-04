#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_10__ {int cbStruct; void* sCleanupProvider; void* sTestPolicyProvider; void* sFinalPolicyProvider; void* sCertificatePolicyProvider; void* sCertificateProvider; void* sSignatureProvider; void* sObjectProvider; void* sInitProvider; } ;
struct TYPE_8__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_9__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  TYPE_2__ GUID ;
typedef  void* CRYPT_TRUST_REG_ENTRY ;
typedef  TYPE_3__ CRYPT_REGISTER_ACTIONID ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pWintrustAddActionID (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int pWintrustRemoveActionID (TYPE_2__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_AddRem_ActionID(void)
{
    static WCHAR DummyDllW[]      = {'d','e','a','d','b','e','e','f','.','d','l','l',0 };
    static WCHAR DummyFunctionW[] = {'d','u','m','m','y','f','u','n','c','t','i','o','n',0 };
    GUID ActionID = { 0xdeadbeef, 0xdead, 0xbeef, { 0xde,0xad,0xbe,0xef,0xde,0xad,0xbe,0xef }};
    CRYPT_REGISTER_ACTIONID ActionIDFunctions;
    CRYPT_TRUST_REG_ENTRY EmptyProvider = { 0, NULL, NULL };
    CRYPT_TRUST_REG_ENTRY DummyProvider = { sizeof(CRYPT_TRUST_REG_ENTRY), DummyDllW, DummyFunctionW };
    BOOL ret;

    if (!pWintrustAddActionID || !pWintrustRemoveActionID)
    {
        win_skip("WintrustAddActionID and/or WintrustRemoveActionID are not available\n");
        return;
    }

    /* All NULL */
    SetLastError(0xdeadbeef);
    ret = pWintrustAddActionID(NULL, 0, NULL);
    ok (!ret, "Expected WintrustAddActionID to fail.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER /* XP/W2K3 */ ||
        GetLastError() == 0xdeadbeef              /* Win98/NT4/W2K */,
        "Expected ERROR_INVALID_PARAMETER(W2K3) or 0xdeadbeef(Win98/NT4/W2K), got %u.\n", GetLastError());

    /* NULL functions */
    SetLastError(0xdeadbeef);
    ret = pWintrustAddActionID(&ActionID, 0, NULL);
    ok (!ret, "Expected WintrustAddActionID to fail.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER /* XP/W2K3 */ ||
        GetLastError() == 0xdeadbeef              /* Win98/NT4/W2K */,
        "Expected ERROR_INVALID_PARAMETER(W2K3) or 0xdeadbeef(Win98/NT4/W2K), got %u.\n", GetLastError());

    /* All OK (although no functions defined), except cbStruct is not set in ActionIDFunctions */
    SetLastError(0xdeadbeef);
    memset(&ActionIDFunctions, 0, sizeof(CRYPT_REGISTER_ACTIONID));
    ret = pWintrustAddActionID(&ActionID, 0, &ActionIDFunctions);
    ok (!ret, "Expected WintrustAddActionID to fail.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER /* XP/W2K3 */ ||
        GetLastError() == 0xdeadbeef              /* Win98/NT4/W2K */,
        "Expected ERROR_INVALID_PARAMETER(W2K3) or 0xdeadbeef(Win98/NT4/W2K), got %u.\n", GetLastError());

    /* All OK (although no functions defined) and cbStruct is set now */
    SetLastError(0xdeadbeef);
    memset(&ActionIDFunctions, 0, sizeof(CRYPT_REGISTER_ACTIONID));
    ActionIDFunctions.cbStruct = sizeof(CRYPT_REGISTER_ACTIONID);
    ret = pWintrustAddActionID(&ActionID, 0, &ActionIDFunctions);
    ok (ret, "Expected WintrustAddActionID to succeed.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %u.\n", GetLastError());

    /* All OK and all (but 1) functions are correctly defined. The DLL and entrypoints
     * are not present.
     */
    memset(&ActionIDFunctions, 0, sizeof(CRYPT_REGISTER_ACTIONID));
    ActionIDFunctions.cbStruct = sizeof(CRYPT_REGISTER_ACTIONID);
    ActionIDFunctions.sInitProvider = DummyProvider;
    ActionIDFunctions.sObjectProvider = DummyProvider;
    ActionIDFunctions.sSignatureProvider = EmptyProvider;
    ActionIDFunctions.sCertificateProvider = DummyProvider;
    ActionIDFunctions.sCertificatePolicyProvider = DummyProvider;
    ActionIDFunctions.sFinalPolicyProvider = DummyProvider;
    ActionIDFunctions.sTestPolicyProvider = DummyProvider;
    ActionIDFunctions.sCleanupProvider = DummyProvider;
    SetLastError(0xdeadbeef);
    ret = pWintrustAddActionID(&ActionID, 0, &ActionIDFunctions);
    ok (ret, "Expected WintrustAddActionID to succeed.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER ||
        GetLastError() == ERROR_ACCESS_DENIED,
        "Expected ERROR_INVALID_PARAMETER or ERROR_ACCESS_DENIED, got %u.\n",
        GetLastError());

    /* All OK and all functions are correctly defined. The DLL and entrypoints
     * are not present.
     */
    memset(&ActionIDFunctions, 0, sizeof(CRYPT_REGISTER_ACTIONID));
    ActionIDFunctions.cbStruct = sizeof(CRYPT_REGISTER_ACTIONID);
    ActionIDFunctions.sInitProvider = DummyProvider;
    ActionIDFunctions.sObjectProvider = DummyProvider;
    ActionIDFunctions.sSignatureProvider = DummyProvider;
    ActionIDFunctions.sCertificateProvider = DummyProvider;
    ActionIDFunctions.sCertificatePolicyProvider = DummyProvider;
    ActionIDFunctions.sFinalPolicyProvider = DummyProvider;
    ActionIDFunctions.sTestPolicyProvider = DummyProvider;
    ActionIDFunctions.sCleanupProvider = DummyProvider;
    SetLastError(0xdeadbeef);
    ret = pWintrustAddActionID(&ActionID, 0, &ActionIDFunctions);
    ok (ret, "Expected WintrustAddActionID to succeed.\n");
    ok (GetLastError() == 0xdeadbeef || GetLastError() == ERROR_ACCESS_DENIED,
        "Expected 0xdeadbeef or ERROR_ACCESS_DENIED, got %u.\n",
        GetLastError());

    SetLastError(0xdeadbeef);
    ret = pWintrustRemoveActionID(&ActionID);
    ok ( ret, "WintrustRemoveActionID failed : %d\n", GetLastError());
    ok ( GetLastError() == 0xdeadbeef, "Last error should not have been changed: %u\n", GetLastError());

    /* NULL input */
    SetLastError(0xdeadbeef);
    ret = pWintrustRemoveActionID(NULL);
    ok (ret, "Expected WintrustRemoveActionID to succeed.\n");
    ok (GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %u.\n", GetLastError());

    /* The passed GUID is removed by a previous call, so it's basically a test with a nonexistent Trust provider */ 
    SetLastError(0xdeadbeef);
    ret = pWintrustRemoveActionID(&ActionID);
    ok (ret, "Expected WintrustRemoveActionID to succeed.\n");
    ok (GetLastError() == 0xdeadbeef,
        "Expected 0xdeadbeef, got %u.\n", GetLastError());
}