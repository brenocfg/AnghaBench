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
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ConvertSidToStringSidA (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ ERROR_NONE_MAPPED ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 scalar_t__ LookupAccountSidA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int*,char*,int*,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*,...) ; 

__attribute__((used)) static void test_sid_str(PSID * sid)
{
    char *str_sid;
    BOOL ret = ConvertSidToStringSidA(sid, &str_sid);
    ok(ret, "ConvertSidToStringSidA() failed: %d\n", GetLastError());
    if (ret)
    {
        char account[MAX_PATH], domain[MAX_PATH];
        SID_NAME_USE use;
        DWORD acc_size = MAX_PATH;
        DWORD dom_size = MAX_PATH;
        ret = LookupAccountSidA (NULL, sid, account, &acc_size, domain, &dom_size, &use);
        ok(ret || GetLastError() == ERROR_NONE_MAPPED,
           "LookupAccountSid(%s) failed: %d\n", str_sid, GetLastError());
        if (ret)
            trace(" %s %s\\%s %d\n", str_sid, domain, account, use);
        else if (GetLastError() == ERROR_NONE_MAPPED)
            trace(" %s couldn't be mapped\n", str_sid);
        LocalFree(str_sid);
    }
}