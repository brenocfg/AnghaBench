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
typedef  int /*<<< orphan*/  PDSROLE_PRIMARY_DOMAIN_INFO_BASIC ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int DsRolePrimaryDomainInfoBasic ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pDsRoleGetPrimaryDomainInformation (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_params(void)
{
    DWORD ret;
    PDSROLE_PRIMARY_DOMAIN_INFO_BASIC dpdi;

    SetLastError(0xdeadbeef);
    ret = pDsRoleGetPrimaryDomainInformation(NULL, DsRolePrimaryDomainInfoBasic, NULL);
    ok( ret == ERROR_INVALID_PARAMETER, "Expected error ERROR_INVALID_PARAMETER, got (%d)\n", ret);

    SetLastError(0xdeadbeef);
    ret = pDsRoleGetPrimaryDomainInformation(NULL, 0, NULL);
    ok( ret == ERROR_INVALID_PARAMETER, "Expected error ERROR_INVALID_PARAMETER, got (%d)\n", ret);
    SetLastError(0xdeadbeef);
    ret = pDsRoleGetPrimaryDomainInformation(NULL, 4, NULL);
    ok( ret == ERROR_INVALID_PARAMETER, "Expected error ERROR_INVALID_PARAMETER, got (%d)\n", ret);

    SetLastError(0xdeadbeef);
    ret = pDsRoleGetPrimaryDomainInformation(NULL, 4, (PBYTE *)&dpdi);
    ok( ret == ERROR_INVALID_PARAMETER, "Expected error ERROR_INVALID_PARAMETER, got (%d)\n", ret);
}