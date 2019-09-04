#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {int dwFlags; int /*<<< orphan*/  grbitEnabledProtocols; } ;
struct TYPE_9__ {int member_0; int /*<<< orphan*/  pvBuffer; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_8__ {int member_1; TYPE_2__* member_2; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SecBufferDesc ;
typedef  TYPE_2__ SecBuffer ;
typedef  int /*<<< orphan*/  SEC_CHAR ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_3__ SCHANNEL_CRED ;
typedef  int /*<<< orphan*/  CtxtHandle ;
typedef  int /*<<< orphan*/  CredHandle ;

/* Variables and functions */
 scalar_t__ AcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeContextBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 int ISC_REQ_ALLOCATE_MEMORY ; 
 int ISC_REQ_CONFIDENTIALITY ; 
 int ISC_REQ_STREAM ; 
 scalar_t__ InitializeSecurityContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SCH_CRED_MANUAL_CRED_VALIDATION ; 
 int SCH_CRED_NO_DEFAULT_CREDS ; 
 int /*<<< orphan*/  SECBUFFER_EMPTY ; 
 int /*<<< orphan*/  SECBUFFER_TOKEN ; 
 int /*<<< orphan*/  SECBUFFER_VERSION ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  SP_PROT_TLS1_CLIENT ; 
 scalar_t__ UNISP_NAME_A ; 
 int /*<<< orphan*/  init_cred (TYPE_3__*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_InitializeSecurityContext(void)
{
    SCHANNEL_CRED cred;
    CredHandle cred_handle;
    CtxtHandle context;
    SECURITY_STATUS status;
    SecBuffer out_buffer = {1000, SECBUFFER_TOKEN, NULL};
    SecBuffer in_buffer = {0, SECBUFFER_EMPTY, NULL};
    SecBufferDesc out_buffers = {SECBUFFER_VERSION, 1, &out_buffer};
    SecBufferDesc in_buffers  = {SECBUFFER_VERSION, 1, &in_buffer};
    ULONG attrs;

    init_cred(&cred);
    cred.grbitEnabledProtocols = SP_PROT_TLS1_CLIENT;
    cred.dwFlags = SCH_CRED_NO_DEFAULT_CREDS|SCH_CRED_MANUAL_CRED_VALIDATION;
    status = AcquireCredentialsHandleA(NULL, (SEC_CHAR *)UNISP_NAME_A, SECPKG_CRED_OUTBOUND, NULL,
        &cred, NULL, NULL, &cred_handle, NULL);
    ok(status == SEC_E_OK, "AcquireCredentialsHandleA failed: %08x\n", status);
    if (status != SEC_E_OK) return;

    status = InitializeSecurityContextA(&cred_handle, NULL, (SEC_CHAR *)"localhost",
        ISC_REQ_CONFIDENTIALITY|ISC_REQ_STREAM|ISC_REQ_ALLOCATE_MEMORY,
        0, 0, &in_buffers, 0, &context, &out_buffers, &attrs, NULL);
    ok(status == SEC_I_CONTINUE_NEEDED, "Expected SEC_I_CONTINUE_NEEDED, got %08x\n", status);

    FreeContextBuffer(out_buffer.pvBuffer);
    DeleteSecurityContext(&context);
    FreeCredentialsHandle(&cred_handle);
}