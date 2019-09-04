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
typedef  int /*<<< orphan*/  wk_sid ;
typedef  char const* WELL_KNOWN_SID_TYPE ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  char const* SID_NAME_USE ;
typedef  TYPE_1__ SID_IDENTIFIER_AUTHORITY ;
typedef  char* PSID ;
typedef  char* LPSTR ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateAndInitializeSid (TYPE_1__*,int,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ ERROR_NONE_MAPPED ; 
 int /*<<< orphan*/  EqualSid (char*,char*) ; 
 int /*<<< orphan*/  FreeSid (char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int LookupAccountNameA (int /*<<< orphan*/ *,char const*,char*,scalar_t__*,char*,scalar_t__*,char const**) ; 
 int SECURITY_MAX_SID_SIZE ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  SECURITY_NT_NON_UNIQUE ; 
 char const* SidTypeWellKnownGroup ; 
 int /*<<< orphan*/  debugstr_sid (char*) ; 
 int get_sid_info (char*,char**,char**) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCreateWellKnownSid (char const*,char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  win_skip (char*,char const*) ; 

__attribute__((used)) static void check_wellknown_name(const char* name, WELL_KNOWN_SID_TYPE result)
{
    SID_IDENTIFIER_AUTHORITY ident = { SECURITY_NT_AUTHORITY };
    PSID domainsid = NULL;
    char wk_sid[SECURITY_MAX_SID_SIZE];
    DWORD cb;

    DWORD sid_size, domain_size;
    SID_NAME_USE sid_use;
    LPSTR domain, account, sid_domain, wk_domain, wk_account;
    PSID psid;
    BOOL ret ,ret2;

    sid_size = 0;
    domain_size = 0;
    ret = LookupAccountNameA(NULL, name, NULL, &sid_size, NULL, &domain_size, &sid_use);
    ok(!ret, " %s Should have failed to lookup account name\n", name);
    psid = HeapAlloc(GetProcessHeap(),0,sid_size);
    domain = HeapAlloc(GetProcessHeap(),0,domain_size);
    ret = LookupAccountNameA(NULL, name, psid, &sid_size, domain, &domain_size, &sid_use);

    if (!result)
    {
        ok(!ret, " %s Should have failed to lookup account name\n",name);
        goto cleanup;
    }

    AllocateAndInitializeSid(&ident, 6, SECURITY_NT_NON_UNIQUE, 12, 23, 34, 45, 56, 0, 0, &domainsid);
    cb = sizeof(wk_sid);
    if (!pCreateWellKnownSid(result, domainsid, wk_sid, &cb))
    {
        win_skip("SID %i is not available on the system\n",result);
        goto cleanup;
    }

    ret2 = get_sid_info(wk_sid, &wk_account, &wk_domain);
    if (!ret2 && GetLastError() == ERROR_NONE_MAPPED)
    {
        win_skip("CreateWellKnownSid() succeeded but the account '%s' is not present (W2K)\n", name);
        goto cleanup;
    }

    get_sid_info(psid, &account, &sid_domain);

    ok(ret, "Failed to lookup account name %s\n",name);
    ok(sid_size != 0, "sid_size was zero\n");

    ok(EqualSid(psid,wk_sid),"%s Sid %s fails to match well known sid %s!\n",
       name, debugstr_sid(psid), debugstr_sid(wk_sid));

    ok(!lstrcmpA(account, wk_account), "Expected %s , got %s\n", account, wk_account);
    ok(!lstrcmpA(domain, wk_domain), "Expected %s, got %s\n", wk_domain, domain);
    ok(sid_use == SidTypeWellKnownGroup , "Expected Use (5), got %d\n", sid_use);

cleanup:
    FreeSid(domainsid);
    HeapFree(GetProcessHeap(),0,psid);
    HeapFree(GetProcessHeap(),0,domain);
}