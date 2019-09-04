#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t GroupCount; TYPE_1__* Groups; } ;
struct TYPE_6__ {int Attributes; int /*<<< orphan*/  Sid; } ;
typedef  TYPE_2__* PTOKEN_GROUPS ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int DuplicateToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_NO_IMPERSONATION_TOKEN ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetTokenInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,size_t,size_t*) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int SE_GROUP_ENABLED ; 
 int /*<<< orphan*/  SecurityImpersonation ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TOKEN_DUPLICATE ; 
 int TOKEN_QUERY ; 
 int TRUE ; 
 int /*<<< orphan*/  TokenGroups ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCheckTokenMembership (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CheckTokenMembership(void)
{
    PTOKEN_GROUPS token_groups;
    DWORD size;
    HANDLE process_token, token;
    BOOL is_member;
    BOOL ret;
    DWORD i;

    if (!pCheckTokenMembership)
    {
        win_skip("CheckTokenMembership is not available\n");
        return;
    }
    ret = OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE|TOKEN_QUERY, &process_token);
    ok(ret, "OpenProcessToken failed with error %d\n", GetLastError());

    ret = DuplicateToken(process_token, SecurityImpersonation, &token);
    ok(ret, "DuplicateToken failed with error %d\n", GetLastError());

    /* groups */
    ret = GetTokenInformation(token, TokenGroups, NULL, 0, &size);
    ok(!ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
        "GetTokenInformation(TokenGroups) %s with error %d\n",
        ret ? "succeeded" : "failed", GetLastError());
    token_groups = HeapAlloc(GetProcessHeap(), 0, size);
    ret = GetTokenInformation(token, TokenGroups, token_groups, size, &size);
    ok(ret, "GetTokenInformation(TokenGroups) failed with error %d\n", GetLastError());

    for (i = 0; i < token_groups->GroupCount; i++)
    {
        if (token_groups->Groups[i].Attributes & SE_GROUP_ENABLED)
            break;
    }

    if (i == token_groups->GroupCount)
    {
        HeapFree(GetProcessHeap(), 0, token_groups);
        CloseHandle(token);
        skip("user not a member of any group\n");
        return;
    }

    is_member = FALSE;
    ret = pCheckTokenMembership(token, token_groups->Groups[i].Sid, &is_member);
    ok(ret, "CheckTokenMembership failed with error %d\n", GetLastError());
    ok(is_member, "CheckTokenMembership should have detected sid as member\n");

    is_member = FALSE;
    ret = pCheckTokenMembership(NULL, token_groups->Groups[i].Sid, &is_member);
    ok(ret, "CheckTokenMembership failed with error %d\n", GetLastError());
    ok(is_member, "CheckTokenMembership should have detected sid as member\n");

    is_member = TRUE;
    SetLastError(0xdeadbeef);
    ret = pCheckTokenMembership(process_token, token_groups->Groups[i].Sid, &is_member);
    ok(!ret && GetLastError() == ERROR_NO_IMPERSONATION_TOKEN,
        "CheckTokenMembership with process token %s with error %d\n",
        ret ? "succeeded" : "failed", GetLastError());
    ok(!is_member, "CheckTokenMembership should have cleared is_member\n");

    HeapFree(GetProcessHeap(), 0, token_groups);
    CloseHandle(token);
    CloseHandle(process_token);
}