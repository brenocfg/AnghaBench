#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/ ************ Sid; } ;
struct TYPE_6__ {TYPE_1__ User; } ;
typedef  TYPE_2__ TOKEN_USER ;
typedef  TYPE_3__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/ ******** PSID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_INVALID_SID ; 
 int /*<<< orphan*/  ERROR_NO_TOKEN ; 
 int EqualSid (int /*<<< orphan*/ ********,int /*<<< orphan*/ ********) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetSidLengthRequired (int) ; 
 int /*<<< orphan*/ * GetSidSubAuthority (int /*<<< orphan*/ ********,int) ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InitializeSid (int /*<<< orphan*/ ********,TYPE_3__*,int) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenThreadToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SECURITY_MAX_SID_SIZE ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TOKEN_READ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TokenUser ; 
 int debugstr_sid (int /*<<< orphan*/ ********) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetWindowsAccountDomainSid (int /*<<< orphan*/ ********,int /*<<< orphan*/ ********,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetWindowsAccountDomainSid(void)
{
    char *user, buffer1[SECURITY_MAX_SID_SIZE], buffer2[SECURITY_MAX_SID_SIZE];
    SID_IDENTIFIER_AUTHORITY domain_ident = { SECURITY_NT_AUTHORITY };
    PSID domain_sid = (PSID *)&buffer1;
    PSID domain_sid2 = (PSID *)&buffer2;
    DWORD sid_size;
    PSID user_sid;
    HANDLE token;
    BOOL bret = TRUE;
    int i;

    if (!pGetWindowsAccountDomainSid)
    {
        win_skip("GetWindowsAccountDomainSid not available\n");
        return;
    }

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_READ, TRUE, &token))
    {
        if (GetLastError() != ERROR_NO_TOKEN) bret = FALSE;
        else if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &token)) bret = FALSE;
    }
    if (!bret)
    {
        win_skip("Failed to get current user token\n");
        return;
    }

    bret = GetTokenInformation(token, TokenUser, NULL, 0, &sid_size);
    ok(!bret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "GetTokenInformation(TokenUser) failed with error %d\n", GetLastError());
    user = HeapAlloc(GetProcessHeap(), 0, sid_size);
    bret = GetTokenInformation(token, TokenUser, user, sid_size, &sid_size);
    ok(bret, "GetTokenInformation(TokenUser) failed with error %d\n", GetLastError());
    CloseHandle(token);
    user_sid = ((TOKEN_USER *)user)->User.Sid;

    SetLastError(0xdeadbeef);
    bret = pGetWindowsAccountDomainSid(0, 0, 0);
    ok(!bret, "GetWindowsAccountDomainSid succeeded\n");
    ok(GetLastError() == ERROR_INVALID_SID, "expected ERROR_INVALID_SID, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    bret = pGetWindowsAccountDomainSid(user_sid, 0, 0);
    ok(!bret, "GetWindowsAccountDomainSid succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    sid_size = SECURITY_MAX_SID_SIZE;
    SetLastError(0xdeadbeef);
    bret = pGetWindowsAccountDomainSid(user_sid, 0, &sid_size);
    ok(!bret, "GetWindowsAccountDomainSid succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    ok(sid_size == GetSidLengthRequired(4), "expected size %d, got %d\n", GetSidLengthRequired(4), sid_size);

    SetLastError(0xdeadbeef);
    bret = pGetWindowsAccountDomainSid(user_sid, domain_sid, 0);
    ok(!bret, "GetWindowsAccountDomainSid succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    sid_size = 1;
    SetLastError(0xdeadbeef);
    bret = pGetWindowsAccountDomainSid(user_sid, domain_sid, &sid_size);
    ok(!bret, "GetWindowsAccountDomainSid succeeded\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    ok(sid_size == GetSidLengthRequired(4), "expected size %d, got %d\n", GetSidLengthRequired(4), sid_size);

    sid_size = SECURITY_MAX_SID_SIZE;
    bret = pGetWindowsAccountDomainSid(user_sid, domain_sid, &sid_size);
    ok(bret, "GetWindowsAccountDomainSid failed with error %d\n", GetLastError());
    ok(sid_size == GetSidLengthRequired(4), "expected size %d, got %d\n", GetSidLengthRequired(4), sid_size);
    InitializeSid(domain_sid2, &domain_ident, 4);
    for (i = 0; i < 4; i++)
        *GetSidSubAuthority(domain_sid2, i) = *GetSidSubAuthority(user_sid, i);
    ok(EqualSid(domain_sid, domain_sid2), "unexpected domain sid %s != %s\n",
       debugstr_sid(domain_sid), debugstr_sid(domain_sid2));

    HeapFree(GetProcessHeap(), 0, user);
}