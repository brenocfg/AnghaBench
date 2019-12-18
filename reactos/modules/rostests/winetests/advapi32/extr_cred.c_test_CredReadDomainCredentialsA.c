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
struct TYPE_3__ {char* member_0; char* member_2; int /*<<< orphan*/ * DnsServerName; int /*<<< orphan*/ * TargetName; int /*<<< orphan*/ * member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/ * member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  PCREDENTIALA ;
typedef  int DWORD ;
typedef  TYPE_1__ CREDENTIAL_TARGET_INFORMATIONA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCredReadDomainCredentialsA (TYPE_1__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CredReadDomainCredentialsA(void)
{
    BOOL ret;
    char target_name[] = "no_such_target";
    CREDENTIAL_TARGET_INFORMATIONA info = {target_name, NULL, target_name, NULL, NULL, NULL, NULL, 0, 0, NULL};
    DWORD count;
    PCREDENTIALA* creds;

    if (!pCredReadDomainCredentialsA)
    {
        win_skip("CredReadDomainCredentialsA() is not implemented\n");
        return;
    }

    /* these two tests would crash on both native and Wine. Implementations
     * does not check for NULL output pointers and try to zero them out early */
if(0)
{
    ret = pCredReadDomainCredentialsA(&info, 0, NULL, &creds);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER, "!\n");
    ret = pCredReadDomainCredentialsA(&info, 0, &count, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER, "!\n");
}

    SetLastError(0xdeadbeef);
    ret = pCredReadDomainCredentialsA(NULL, 0, &count, &creds);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "CredReadDomainCredentialsA should have failed with ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    SetLastError(0xdeadbeef);
    creds = (void*)0x12345;
    count = 2;
    ret = pCredReadDomainCredentialsA(&info, 0, &count, &creds);
    ok(!ret && GetLastError() == ERROR_NOT_FOUND,
        "CredReadDomainCredentialsA should have failed with ERROR_NOT_FOUND instead of %d\n",
        GetLastError());
    ok(count ==0 && creds == NULL, "CredReadDomainCredentialsA must not return any result\n");

    info.TargetName = NULL;

    SetLastError(0xdeadbeef);
    ret = pCredReadDomainCredentialsA(&info, 0, &count, &creds);
    ok(!ret, "CredReadDomainCredentialsA should have failed\n");
    ok(GetLastError() == ERROR_NOT_FOUND ||
        GetLastError() == ERROR_INVALID_PARAMETER, /* Vista, W2K8 */
        "Expected ERROR_NOT_FOUND or ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    info.DnsServerName = NULL;

    SetLastError(0xdeadbeef);
    ret = pCredReadDomainCredentialsA(&info, 0, &count, &creds);
    ok(!ret, "CredReadDomainCredentialsA should have failed\n");
    ok(GetLastError() == ERROR_NOT_FOUND ||
        GetLastError() == ERROR_INVALID_PARAMETER, /* Vista, W2K8 */
        "Expected ERROR_NOT_FOUND or ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());
}