#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_12__ {TYPE_1__* pBuffers; } ;
struct TYPE_11__ {unsigned char* User; unsigned char* Domain; unsigned char* Password; int /*<<< orphan*/  Flags; void* PasswordLength; void* DomainLength; void* UserLength; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  cred; int /*<<< orphan*/  ctxt; TYPE_6__* out_buf; TYPE_4__* id; TYPE_2__ member_0; } ;
struct TYPE_8__ {int* pvBuffer; } ;
typedef  TYPE_3__ SspiData ;
typedef  TYPE_4__ SEC_WINNT_AUTH_IDENTITY_A ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  int /*<<< orphan*/ * PSecPkgInfoA ;
typedef  int* PBYTE ;

/* Variables and functions */
 scalar_t__ ISC_REQ_CONFIDENTIALITY ; 
 scalar_t__ ISC_REQ_CONNECTION ; 
 scalar_t__ ISC_REQ_DELEGATE ; 
 scalar_t__ ISC_REQ_EXTENDED_ERROR ; 
 scalar_t__ ISC_REQ_INTEGRITY ; 
 scalar_t__ ISC_REQ_MUTUAL_AUTH ; 
 scalar_t__ ISC_REQ_REPLAY_DETECT ; 
 scalar_t__ ISC_REQ_SEQUENCE_DETECT ; 
 scalar_t__ ISC_REQ_USE_DCE_STYLE ; 
 int /*<<< orphan*/  SECURITY_NETWORK_DREP ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  SEC_WINNT_AUTH_IDENTITY_ANSI ; 
 int /*<<< orphan*/  cleanupBuffers (TYPE_3__*) ; 
 int /*<<< orphan*/  getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pDeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeContextBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ pInitializeSecurityContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sec_pkg_name ; 
 scalar_t__ setupClient (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ) ; 
 void* strlen (char*) ; 
 scalar_t__ test_pass ; 
 scalar_t__ test_user ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ workgroup ; 

__attribute__((used)) static void testInitializeSecurityContextFlags(void)
{
    SECURITY_STATUS         sec_status;
    PSecPkgInfoA            pkg_info = NULL;
    SspiData                client = {{0}};
    SEC_WINNT_AUTH_IDENTITY_A id;
    ULONG                   req_attr, ctxt_attr;
    TimeStamp               ttl;
    PBYTE                   packet;

    if(pQuerySecurityPackageInfoA( sec_pkg_name, &pkg_info) != SEC_E_OK)
    {
        ok(0, "NTLM package not installed, skipping test.\n");
        return;
    }

    pFreeContextBuffer(pkg_info);
    id.User = (unsigned char*) test_user;
    id.UserLength = strlen((char *) id.User);
    id.Domain = (unsigned char *) workgroup;
    id.DomainLength = strlen((char *) id.Domain);
    id.Password = (unsigned char*) test_pass;
    id.PasswordLength = strlen((char *) id.Password);
    id.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;

    client.id = &id;

    if((sec_status = setupClient(&client, sec_pkg_name)) != SEC_E_OK)
    {
        skip("Setting up the client returned %s, skipping test!\n",
                getSecError(sec_status));
        return;
    }

    packet = client.out_buf->pBuffers[0].pvBuffer;

    /* Due to how the requesting of the flags is implemented in ntlm_auth,
     * the tests need to be in this order, as there is no way to specify
     * "I request no special features" in ntlm_auth */

    /* Without any flags, the lowest byte should not have bits 0x20 or 0x10 set*/
    req_attr = 0;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok(((packet[12] & 0x10) == 0) && ((packet[12] & 0x20) == 0),
            "With req_attr == 0, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_CONNECTION, the lowest byte should not have bits 0x20 or 0x10 set*/
    req_attr = ISC_REQ_CONNECTION;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok(((packet[12] & 0x10) == 0) && ((packet[12] & 0x20) == 0),
            "For ISC_REQ_CONNECTION, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_EXTENDED_ERROR, the lowest byte should not have bits 0x20 or 0x10 set*/
    req_attr = ISC_REQ_EXTENDED_ERROR;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok(((packet[12] & 0x10) == 0) && ((packet[12] & 0x20) == 0),
            "For ISC_REQ_EXTENDED_ERROR, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_MUTUAL_AUTH, the lowest byte should not have bits 0x20 or 0x10 set*/
    req_attr = ISC_REQ_MUTUAL_AUTH;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok(((packet[12] & 0x10) == 0) && ((packet[12] & 0x20) == 0),
            "For ISC_REQ_MUTUAL_AUTH, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_USE_DCE_STYLE, the lowest byte should not have bits 0x20 or 0x10 set*/
    req_attr = ISC_REQ_USE_DCE_STYLE;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok(((packet[12] & 0x10) == 0) && ((packet[12] & 0x20) == 0),
            "For ISC_REQ_USE_DCE_STYLE, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_DELEGATE, the lowest byte should not have bits 0x20 or 0x10 set*/
    req_attr = ISC_REQ_DELEGATE;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok(((packet[12] & 0x10) == 0) && ((packet[12] & 0x20) == 0),
            "For ISC_REQ_DELEGATE, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_INTEGRITY, the lowest byte should have bit 0x10 set */
    req_attr = ISC_REQ_INTEGRITY;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok((packet[12] & 0x10) != 0,
            "For ISC_REQ_INTEGRITY, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_REPLAY_DETECT, the lowest byte should have bit 0x10 set */
    req_attr = ISC_REQ_REPLAY_DETECT;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok((packet[12] & 0x10) != 0,
            "For ISC_REQ_REPLAY_DETECT, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_SEQUENCE_DETECT, the lowest byte should have bit 0x10 set */
    req_attr = ISC_REQ_SEQUENCE_DETECT;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok((packet[12] & 0x10) != 0,
            "For ISC_REQ_SEQUENCE_DETECT, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

    /* With ISC_REQ_CONFIDENTIALITY, the lowest byte should have bit 0x20 set */
    req_attr = ISC_REQ_CONFIDENTIALITY;

    if((sec_status = pInitializeSecurityContextA(&client.cred, NULL, NULL, req_attr,
        0, SECURITY_NETWORK_DREP, NULL, 0, &client.ctxt, client.out_buf,
        &ctxt_attr, &ttl)) != SEC_I_CONTINUE_NEEDED)
    {
        trace("InitializeSecurityContext returned %s not SEC_I_CONTINUE_NEEDED, aborting.\n",
                getSecError(sec_status));
        goto tISCFend;
    }

    ok((packet[12] & 0x20) != 0,
            "For ISC_REQ_CONFIDENTIALITY, flags are 0x%02x%02x%02x%02x.\n",
            packet[15], packet[14], packet[13], packet[12]);
    pDeleteSecurityContext(&client.ctxt);

tISCFend:
    cleanupBuffers(&client);
    pFreeCredentialsHandle(&client.cred);
}