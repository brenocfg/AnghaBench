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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/ * PSID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/ ***** PSID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * GetSidIdentifierAuthority (int /*<<< orphan*/ *****) ; 
 scalar_t__ IsValidSid (int /*<<< orphan*/ *****) ; 
 int SECURITY_MAX_SID_SIZE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetSidIdentifierAuthority ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetSidIdentifierAuthority(void)
{
    char buffer[SECURITY_MAX_SID_SIZE];
    PSID authority_sid = (PSID *)buffer;
    PSID_IDENTIFIER_AUTHORITY id;
    BOOL ret;

    if (!pGetSidIdentifierAuthority)
    {
        win_skip("GetSidIdentifierAuthority not available\n");
        return;
    }

    memset(buffer, 0xcc, sizeof(buffer));
    ret = IsValidSid(authority_sid);
    ok(!ret, "expected FALSE, got %u\n", ret);

    SetLastError(0xdeadbeef);
    id = GetSidIdentifierAuthority(authority_sid);
    ok(id != NULL, "got NULL pointer as identifier authority\n");
    ok(GetLastError() == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    id = GetSidIdentifierAuthority(NULL);
    ok(id != NULL, "got NULL pointer as identifier authority\n");
    ok(GetLastError() == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());
}