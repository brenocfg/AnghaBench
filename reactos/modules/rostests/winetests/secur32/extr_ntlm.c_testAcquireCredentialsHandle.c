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
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_3__ {unsigned char* User; unsigned char* Domain; unsigned char* Password; void* PasswordLength; void* UserLength; void* DomainLength; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ SEC_WINNT_AUTH_IDENTITY_A ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  int /*<<< orphan*/ * PSecPkgInfoA ;
typedef  int /*<<< orphan*/  CredHandle ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  SEC_WINNT_AUTH_IDENTITY_ANSI ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pAcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeContextBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sec_pkg_name ; 
 void* strlen (char*) ; 
 scalar_t__ test_pass ; 
 scalar_t__ test_user ; 
 scalar_t__ workgroup ; 

__attribute__((used)) static BOOL testAcquireCredentialsHandle(void)
{
    CredHandle cred;
    TimeStamp ttl;
    SECURITY_STATUS ret;
    SEC_WINNT_AUTH_IDENTITY_A id;
    PSecPkgInfoA pkg_info = NULL;

    if(pQuerySecurityPackageInfoA(sec_pkg_name, &pkg_info) != SEC_E_OK)
    {
        ok(0, "NTLM package not installed, skipping test\n");
        return FALSE;
    }
    pFreeContextBuffer(pkg_info);

    id.User = (unsigned char*) test_user;
    id.UserLength = strlen((char *) id.User);
    id.Domain = (unsigned char *) workgroup;
    id.DomainLength = strlen((char *) id.Domain);
    id.Password = (unsigned char*) test_pass;
    id.PasswordLength = strlen((char *) id.Password);
    id.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;

    ret = pAcquireCredentialsHandleA(NULL, sec_pkg_name, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandle() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.DomainLength = 0;
    ret = pAcquireCredentialsHandleA(NULL, sec_pkg_name, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandle() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.Domain = NULL;
    ret = pAcquireCredentialsHandleA(NULL, sec_pkg_name, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandle() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.Domain = (unsigned char *) workgroup;
    id.DomainLength = strlen((char *) id.Domain);
    id.UserLength = 0;
    id.User = NULL;
    ret = pAcquireCredentialsHandleA(NULL, sec_pkg_name, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandle() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.User = (unsigned char*) test_user;
    id.UserLength = strlen((char *) id.User);
    id.Password = NULL;
    id.PasswordLength = 0;
    ret = pAcquireCredentialsHandleA(NULL, sec_pkg_name, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandle() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);
    return TRUE;
}