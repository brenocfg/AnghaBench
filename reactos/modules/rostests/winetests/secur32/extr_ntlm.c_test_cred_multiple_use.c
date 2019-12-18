#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/  cbMaxToken; } ;
struct TYPE_15__ {unsigned char* User; unsigned char* Domain; unsigned char* Password; int /*<<< orphan*/  Flags; void* PasswordLength; void* DomainLength; void* UserLength; } ;
struct TYPE_14__ {int /*<<< orphan*/  pvBuffer; int /*<<< orphan*/  cbBuffer; int /*<<< orphan*/  BufferType; } ;
struct TYPE_13__ {TYPE_2__* pBuffers; int /*<<< orphan*/  cBuffers; int /*<<< orphan*/  ulVersion; } ;
typedef  TYPE_1__ SecBufferDesc ;
typedef  TYPE_2__ SecBuffer ;
typedef  TYPE_3__ SEC_WINNT_AUTH_IDENTITY_A ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_4__* PSecPkgInfoA ;
typedef  TYPE_5__ CtxtHandle ;
typedef  int /*<<< orphan*/  CredHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_REQ_CONNECTION ; 
 int /*<<< orphan*/  SECBUFFER_TOKEN ; 
 int /*<<< orphan*/  SECBUFFER_VERSION ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 int /*<<< orphan*/  SECURITY_NETWORK_DREP ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  SEC_WINNT_AUTH_IDENTITY_ANSI ; 
 scalar_t__ getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pAcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pDeleteSecurityContext (TYPE_5__*) ; 
 int /*<<< orphan*/  pFreeContextBuffer (TYPE_4__*) ; 
 scalar_t__ pFreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ pInitializeSecurityContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  sec_pkg_name ; 
 void* strlen (char*) ; 
 scalar_t__ test_pass ; 
 scalar_t__ test_user ; 
 scalar_t__ workgroup ; 

__attribute__((used)) static void test_cred_multiple_use(void)
{
    SECURITY_STATUS ret;
    SEC_WINNT_AUTH_IDENTITY_A id;
    PSecPkgInfoA            pkg_info = NULL;
    CredHandle              cred;
    CtxtHandle              ctxt1 = {0};
    CtxtHandle              ctxt2 = {0};
    SecBufferDesc           buffer_desc;
    SecBuffer               buffers[1];
    ULONG                   ctxt_attr;
    TimeStamp               ttl;

    if(pQuerySecurityPackageInfoA(sec_pkg_name, &pkg_info) != SEC_E_OK)
    {
        ok(0, "NTLM package not installed, skipping test\n");
        return;
    }
    buffers[0].cbBuffer = pkg_info->cbMaxToken;
    buffers[0].BufferType = SECBUFFER_TOKEN;
    buffers[0].pvBuffer = HeapAlloc(GetProcessHeap(), 0, buffers[0].cbBuffer);

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

    buffer_desc.ulVersion = SECBUFFER_VERSION;
    buffer_desc.cBuffers = ARRAY_SIZE(buffers);
    buffer_desc.pBuffers = buffers;

    ret = pInitializeSecurityContextA(&cred, NULL, NULL, ISC_REQ_CONNECTION,
            0, SECURITY_NETWORK_DREP, NULL, 0, &ctxt1, &buffer_desc,
            &ctxt_attr, &ttl);
    ok(ret == SEC_I_CONTINUE_NEEDED, "InitializeSecurityContextA failed with error 0x%x\n", ret);

    ret = pInitializeSecurityContextA(&cred, NULL, NULL, ISC_REQ_CONNECTION,
            0, SECURITY_NETWORK_DREP, NULL, 0, &ctxt2, &buffer_desc,
            &ctxt_attr, &ttl);
    ok(ret == SEC_I_CONTINUE_NEEDED, "Second InitializeSecurityContextA on cred handle failed with error 0x%x\n", ret);

    ret = pDeleteSecurityContext(&ctxt1);
    ok(ret == SEC_E_OK, "DeleteSecurityContext failed with error 0x%x\n", ret);
    ret = pDeleteSecurityContext(&ctxt2);
    ok(ret == SEC_E_OK, "DeleteSecurityContext failed with error 0x%x\n", ret);
    ret = pFreeCredentialsHandle(&cred);
    ok(ret == SEC_E_OK, "FreeCredentialsHandle failed with error 0x%x\n", ret);

    HeapFree(GetProcessHeap(), 0, buffers[0].pvBuffer);
}