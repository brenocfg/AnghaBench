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
typedef  char* LPSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LookupAccountSidA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int*,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_sid_info(PSID psid, LPSTR *user, LPSTR *dom)
{
    static char account[257], domain[257];
    DWORD user_size, dom_size;
    SID_NAME_USE use;
    BOOL ret;

    *user = account;
    *dom = domain;

    user_size = dom_size = 257;
    account[0] = domain[0] = 0;
    ret = LookupAccountSidA(NULL, psid, account, &user_size, domain, &dom_size, &use);
    ok(ret, "LookupAccountSidA failed %u\n", GetLastError());
}