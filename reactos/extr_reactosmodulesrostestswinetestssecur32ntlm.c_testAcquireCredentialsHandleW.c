#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_4__ {char* User; char* Domain; char* Password; int /*<<< orphan*/  Flags; void* PasswordLength; void* DomainLength; void* UserLength; } ;
typedef  TYPE_1__ SEC_WINNT_AUTH_IDENTITY_W ;
typedef  TYPE_1__ SEC_WINNT_AUTH_IDENTITY_A ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  int /*<<< orphan*/ * PSecPkgInfoA ;
typedef  int /*<<< orphan*/  CredHandle ;

/* Variables and functions */
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  SEC_WINNT_AUTH_IDENTITY_ANSI ; 
 int /*<<< orphan*/  SEC_WINNT_AUTH_IDENTITY_UNICODE ; 
 int /*<<< orphan*/  getSecError (scalar_t__) ; 
 void* lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pAcquireCredentialsHandleW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeContextBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sec_pkg_name ; 
 void* strlen (scalar_t__) ; 
 scalar_t__ test_pass ; 
 scalar_t__ test_user ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ workgroup ; 

__attribute__((used)) static void testAcquireCredentialsHandleW(void)
{
    CredHandle cred;
    TimeStamp ttl;
    static WCHAR sec_pkg_nameW[] = {'N','T','L','M',0 };
    static WCHAR test_userW[]    = {'t','e','s','t','u','s','e','r',0 };
    static WCHAR workgroupW[]    = {'W','O','R','K','G','R','O','U','P',0};
    static WCHAR test_passW[]    = {'t','e','s','t','p','a','s','s',0};
    SECURITY_STATUS ret;
    SEC_WINNT_AUTH_IDENTITY_A idA;
    SEC_WINNT_AUTH_IDENTITY_W id;
    PSecPkgInfoA pkg_info = NULL;

    if(!pAcquireCredentialsHandleW)
    {
        win_skip("AcquireCredentialsHandleW not available\n");
        return;
    }

    if(pQuerySecurityPackageInfoA(sec_pkg_name, &pkg_info) != SEC_E_OK)
    {
        ok(0, "NTLM package not installed, skipping test\n");
        return;
    }
    pFreeContextBuffer(pkg_info);

    id.User = test_userW;
    id.UserLength = lstrlenW(test_userW);
    id.Domain = workgroupW;
    id.DomainLength = lstrlenW(workgroupW);
    id.Password = test_passW;
    id.PasswordLength = lstrlenW(test_passW);
    id.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

    ret = pAcquireCredentialsHandleW(NULL, sec_pkg_nameW, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandeW() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.DomainLength = 0;
    ret = pAcquireCredentialsHandleW(NULL, sec_pkg_nameW, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandeW() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.Domain = NULL;
    ret = pAcquireCredentialsHandleW(NULL, sec_pkg_nameW, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandeW() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.Domain = workgroupW;
    id.DomainLength = lstrlenW(workgroupW);
    id.UserLength = 0;
    id.User = NULL;
    ret = pAcquireCredentialsHandleW(NULL, sec_pkg_nameW, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandeW() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    id.User = test_userW;
    id.UserLength = lstrlenW(test_userW);
    id.Password = test_passW;    /* NULL string causes a crash. */
    id.PasswordLength = 0;
    ret = pAcquireCredentialsHandleW(NULL, sec_pkg_nameW, SECPKG_CRED_OUTBOUND,
            NULL, &id, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandeW() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);

    /* Test using the ASCII structure. */
    idA.User = (unsigned char*) test_user;
    idA.UserLength = strlen(test_user);
    idA.Domain = (unsigned char *) workgroup;
    idA.DomainLength = strlen(workgroup);
    idA.Password = (unsigned char*) test_pass;
    idA.PasswordLength = strlen(test_pass);
    idA.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;

    ret = pAcquireCredentialsHandleW(NULL, sec_pkg_nameW, SECPKG_CRED_OUTBOUND,
            NULL, &idA, NULL, NULL, &cred, &ttl);
    ok(ret == SEC_E_OK, "AcquireCredentialsHandeW() returned %s\n",
            getSecError(ret));
    pFreeCredentialsHandle(&cred);
}