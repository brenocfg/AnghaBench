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
typedef  int /*<<< orphan*/ * PSID ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pConvertStringSidToSidA (char*,int /*<<< orphan*/ **) ; 
 int* pGetSidSubAuthority (int /*<<< orphan*/ *,int) ; 
 int* pGetSidSubAuthorityCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pIsValidSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetSidSubAuthority(void)
{
    PSID psid = NULL;

    if (!pGetSidSubAuthority || !pConvertStringSidToSidA || !pIsValidSid || !pGetSidSubAuthorityCount)
    {
        win_skip("Some functions not available\n");
        return;
    }
    /* Note: on windows passing in an invalid index like -1, lets GetSidSubAuthority return 0x05000000 but
             still GetLastError returns ERROR_SUCCESS then. We don't test these unlikely cornercases here for now */
    ok(pConvertStringSidToSidA("S-1-5-21-93476-23408-4576",&psid),"ConvertStringSidToSidA failed\n");
    ok(pIsValidSid(psid),"Sid is not valid\n");
    SetLastError(0xbebecaca);
    ok(*pGetSidSubAuthorityCount(psid) == 4,"GetSidSubAuthorityCount gave %d expected 4\n",*pGetSidSubAuthorityCount(psid));
    ok(GetLastError() == 0,"GetLastError returned %d instead of 0\n",GetLastError());
    SetLastError(0xbebecaca);
    ok(*pGetSidSubAuthority(psid,0) == 21,"GetSidSubAuthority gave %d expected 21\n",*pGetSidSubAuthority(psid,0));
    ok(GetLastError() == 0,"GetLastError returned %d instead of 0\n",GetLastError());
    SetLastError(0xbebecaca);
    ok(*pGetSidSubAuthority(psid,1) == 93476,"GetSidSubAuthority gave %d expected 93476\n",*pGetSidSubAuthority(psid,1));
    ok(GetLastError() == 0,"GetLastError returned %d instead of 0\n",GetLastError());
    SetLastError(0xbebecaca);
    ok(pGetSidSubAuthority(psid,4) != NULL,"Expected out of bounds GetSidSubAuthority to return a non-NULL pointer\n");
    ok(GetLastError() == 0,"GetLastError returned %d instead of 0\n",GetLastError());
    LocalFree(psid);
}