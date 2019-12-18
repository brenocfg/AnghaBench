#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  cbMaxToken; } ;
struct TYPE_12__ {int /*<<< orphan*/  pvBuffer; int /*<<< orphan*/  cbBuffer; int /*<<< orphan*/  BufferType; } ;
struct TYPE_11__ {TYPE_2__* pBuffers; int /*<<< orphan*/  cBuffers; int /*<<< orphan*/  ulVersion; } ;
typedef  TYPE_1__ SecBufferDesc ;
typedef  TYPE_2__ SecBuffer ;
typedef  int /*<<< orphan*/  SEC_CHAR ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_3__* PSecPkgInfoA ;
typedef  TYPE_4__ CtxtHandle ;
typedef  int /*<<< orphan*/  CredHandle ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_REQ_CONNECTION ; 
 int /*<<< orphan*/  NameSamCompatible ; 
 int /*<<< orphan*/  SECBUFFER_TOKEN ; 
 int /*<<< orphan*/  SECBUFFER_VERSION ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 int /*<<< orphan*/  SECURITY_NETWORK_DREP ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 scalar_t__ getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pAcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pDeleteSecurityContext (TYPE_4__*) ; 
 int /*<<< orphan*/  pFreeContextBuffer (TYPE_3__*) ; 
 scalar_t__ pFreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ pGetUserNameExA (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ pInitializeSecurityContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ *,TYPE_3__**) ; 

__attribute__((used)) static void test_null_auth_data(void)
{
    SECURITY_STATUS status;
    PSecPkgInfoA info;
    CredHandle cred;
    CtxtHandle ctx = {0};
    SecBufferDesc buffer_desc;
    SecBuffer buffers[1];
    char user[256];
    TimeStamp ttl;
    ULONG attr, size;
    BOOLEAN ret;

    if(pQuerySecurityPackageInfoA((SEC_CHAR *)"NTLM", &info) != SEC_E_OK)
    {
        ok(0, "NTLM package not installed, skipping test\n");
        return;
    }

    status = pAcquireCredentialsHandleA(NULL, (SEC_CHAR *)"NTLM", SECPKG_CRED_OUTBOUND,
                                        NULL, NULL, NULL, NULL, &cred, &ttl);
    ok(status == SEC_E_OK, "AcquireCredentialsHandle() failed %s\n", getSecError(status));

    buffers[0].cbBuffer = info->cbMaxToken;
    buffers[0].BufferType = SECBUFFER_TOKEN;
    buffers[0].pvBuffer = HeapAlloc(GetProcessHeap(), 0, buffers[0].cbBuffer);

    buffer_desc.ulVersion = SECBUFFER_VERSION;
    buffer_desc.cBuffers = ARRAY_SIZE(buffers);
    buffer_desc.pBuffers = buffers;

    size = sizeof(user);
    ret = pGetUserNameExA(NameSamCompatible, user, &size);
    ok(ret, "GetUserNameExA failed %u\n", GetLastError());

    status = pInitializeSecurityContextA(&cred, NULL, (SEC_CHAR *)user,
                                         ISC_REQ_CONNECTION, 0, SECURITY_NETWORK_DREP,
                                         NULL, 0, &ctx, &buffer_desc, &attr, &ttl);
    ok(status == SEC_I_CONTINUE_NEEDED, "InitializeSecurityContextA failed %s\n", getSecError(status));

    ret = pDeleteSecurityContext(&ctx);
    ok(ret == SEC_E_OK, "DeleteSecurityContext failed with error 0x%x\n", ret);
    ret = pFreeCredentialsHandle(&cred);
    ok(ret == SEC_E_OK, "FreeCredentialsHandle failed with error 0x%x\n", ret);

    pFreeContextBuffer(info);
    HeapFree(GetProcessHeap(), 0, buffers[0].pvBuffer);
}