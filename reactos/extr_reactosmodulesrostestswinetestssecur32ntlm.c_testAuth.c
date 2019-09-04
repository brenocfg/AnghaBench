#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UINT ;
struct TYPE_26__ {unsigned char* User; unsigned char* Domain; unsigned char* Password; int /*<<< orphan*/  Flags; void* PasswordLength; void* DomainLength; void* UserLength; } ;
struct TYPE_25__ {scalar_t__ NegotiationState; TYPE_3__* PackageInfo; } ;
struct TYPE_24__ {int cbMaxToken; int cbMaxSignature; int cbSecurityTrailer; scalar_t__ cbBlockSize; } ;
struct TYPE_23__ {int fCapabilities; int wVersion; scalar_t__ wRPCID; scalar_t__ Name; char* Comment; } ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int /*<<< orphan*/  cred; int /*<<< orphan*/  ctxt; TYPE_6__* id; TYPE_1__ member_0; } ;
typedef  TYPE_2__ SspiData ;
typedef  TYPE_3__ SecPkgInfoA ;
typedef  TYPE_4__ SecPkgContext_Sizes ;
typedef  TYPE_5__ SecPkgContext_NegotiationInfoA ;
typedef  TYPE_6__ SEC_WINNT_AUTH_IDENTITY_A ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  int /*<<< orphan*/ * PSecPkgInfoA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ FreeContextBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int NTLM_BASE_CAPS ; 
 scalar_t__ QueryContextAttributesA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ RPC_C_AUTHN_WINNT ; 
 int /*<<< orphan*/  SECPKG_ATTR_NEGOTIATION_INFO ; 
 int /*<<< orphan*/  SECPKG_ATTR_SIZES ; 
 int SECPKG_FLAG_APPCONTAINER_CHECKS ; 
 int SECPKG_FLAG_READONLY_WITH_CHECKSUM ; 
 int SECPKG_FLAG_RESTRICTED_TOKENS ; 
 scalar_t__ SECPKG_NEGOTIATION_COMPLETE ; 
 scalar_t__ SEC_E_LOGON_DENIED ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  SEC_WINNT_AUTH_IDENTITY_ANSI ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  cleanupBuffers (TYPE_2__*) ; 
 int /*<<< orphan*/  communicate (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ getSecError (scalar_t__) ; 
 int /*<<< orphan*/  lstrcmpA (scalar_t__,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pDeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeContextBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ pFreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ pQueryContextAttributesA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ runClient (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ runFakeServer (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ runServer (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_pkg_name ; 
 scalar_t__ setupClient (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ setupFakeServer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ setupServer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 void* strlen (char*) ; 
 scalar_t__ test_pass ; 
 scalar_t__ test_user ; 
 int /*<<< orphan*/  trace (char*) ; 
 scalar_t__ workgroup ; 

__attribute__((used)) static void testAuth(ULONG data_rep, BOOL fake)
{
    SECURITY_STATUS         client_stat = SEC_I_CONTINUE_NEEDED;
    SECURITY_STATUS         server_stat = SEC_I_CONTINUE_NEEDED;
    SECURITY_STATUS         sec_status;
    PSecPkgInfoA            pkg_info = NULL;
    BOOL                    first = TRUE;
    SspiData                client = {{0}}, server = {{0}};
    SEC_WINNT_AUTH_IDENTITY_A id;
    SecPkgContext_Sizes     ctxt_sizes;
    SecPkgContext_NegotiationInfoA info;
    SecPkgInfoA *pi;

    if(pQuerySecurityPackageInfoA( sec_pkg_name, &pkg_info)!= SEC_E_OK)
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

    sec_status = setupClient(&client, sec_pkg_name);

    if(sec_status != SEC_E_OK)
    {
        skip("Error: Setting up the client returned %s, exiting test!\n",
                getSecError(sec_status));
        pFreeCredentialsHandle(&client.cred);
        return;
    }

    if(fake)
        sec_status = setupFakeServer(&server, sec_pkg_name);
    else
        sec_status = setupServer(&server, sec_pkg_name);

    if(sec_status != SEC_E_OK)
    {
        skip("Error: Setting up the server returned %s, exiting test!\n",
                getSecError(sec_status));
        pFreeCredentialsHandle(&server.cred);
        pFreeCredentialsHandle(&client.cred);
        return;
    }

    while(client_stat == SEC_I_CONTINUE_NEEDED && server_stat == SEC_I_CONTINUE_NEEDED)
    {
        client_stat = runClient(&client, first, data_rep);

        ok(client_stat == SEC_E_OK || client_stat == SEC_I_CONTINUE_NEEDED,
                "Running the client returned %s, more tests will fail.\n",
                getSecError(client_stat));

        communicate(&client, &server);

        if(fake)
            server_stat = runFakeServer(&server, first, data_rep);
        else
            server_stat = runServer(&server, first, data_rep);

        ok(server_stat == SEC_E_OK || server_stat == SEC_I_CONTINUE_NEEDED ||
                server_stat == SEC_E_LOGON_DENIED,
                "Running the server returned %s, more tests will fail from now.\n",
                getSecError(server_stat));

        communicate(&server, &client);
        trace("Looping\n");
        first = FALSE;
    }

    if(client_stat != SEC_E_OK)
    {
        skip("Authentication failed, skipping test.\n");
        goto tAuthend;
    }

    sec_status = pQueryContextAttributesA(&client.ctxt,
            SECPKG_ATTR_SIZES, &ctxt_sizes);

    ok(sec_status == SEC_E_OK,
            "pQueryContextAttributesA(SECPKG_ATTR_SIZES) returned %s\n",
            getSecError(sec_status));
    ok((ctxt_sizes.cbMaxToken == 1904) || (ctxt_sizes.cbMaxToken == 2888),
            "cbMaxToken should be 1904 or 2888 but is %u\n",
            ctxt_sizes.cbMaxToken);
    ok(ctxt_sizes.cbMaxSignature == 16,
            "cbMaxSignature should be 16 but is %u\n",
            ctxt_sizes.cbMaxSignature);
    ok(ctxt_sizes.cbSecurityTrailer == 16,
            "cbSecurityTrailer should be 16 but is  %u\n",
            ctxt_sizes.cbSecurityTrailer);
    ok(ctxt_sizes.cbBlockSize == 0,
            "cbBlockSize should be 0 but is %u\n",
            ctxt_sizes.cbBlockSize);

    memset(&info, 0, sizeof(info));
    sec_status = QueryContextAttributesA(&client.ctxt, SECPKG_ATTR_NEGOTIATION_INFO, &info);
    ok(sec_status == SEC_E_OK, "QueryContextAttributesA returned %08x\n", sec_status);

    pi = info.PackageInfo;
    ok(info.NegotiationState == SECPKG_NEGOTIATION_COMPLETE, "got %u\n", info.NegotiationState);
    ok(pi != NULL, "expected non-NULL PackageInfo\n");
    if (pi)
    {
        UINT expected, got;
        char *eob;

        ok(pi->fCapabilities == NTLM_BASE_CAPS ||
           pi->fCapabilities == (NTLM_BASE_CAPS|SECPKG_FLAG_READONLY_WITH_CHECKSUM) ||
           pi->fCapabilities == (NTLM_BASE_CAPS|SECPKG_FLAG_RESTRICTED_TOKENS) ||
           pi->fCapabilities == (NTLM_BASE_CAPS|SECPKG_FLAG_RESTRICTED_TOKENS|
                                 SECPKG_FLAG_APPCONTAINER_CHECKS),
           "got %08x\n", pi->fCapabilities);
        ok(pi->wVersion == 1, "got %u\n", pi->wVersion);
        ok(pi->wRPCID == RPC_C_AUTHN_WINNT, "got %u\n", pi->wRPCID);
        ok(!lstrcmpA( pi->Name, "NTLM" ), "got %s\n", pi->Name);

        expected = sizeof(*pi) + lstrlenA(pi->Name) + 1 + lstrlenA(pi->Comment) + 1;
        got = HeapSize(GetProcessHeap(), 0, pi);
        ok(got == expected, "got %u, expected %u\n", got, expected);
        eob = (char *)pi + expected;
        ok(pi->Name + lstrlenA(pi->Name) < eob, "Name doesn't fit into allocated block\n");
        ok(pi->Comment + lstrlenA(pi->Comment) < eob, "Comment doesn't fit into allocated block\n");

        sec_status = FreeContextBuffer(pi);
        ok(sec_status == SEC_E_OK, "FreeContextBuffer error %#x\n", sec_status);
    }

tAuthend:
    cleanupBuffers(&client);
    cleanupBuffers(&server);

    if(!fake)
    {
        sec_status = pDeleteSecurityContext(&server.ctxt);
        ok(sec_status == SEC_E_OK, "DeleteSecurityContext(server) returned %s\n",
            getSecError(sec_status));
    }

    sec_status = pDeleteSecurityContext(&client.ctxt);
    ok(sec_status == SEC_E_OK, "DeleteSecurityContext(client) returned %s\n",
            getSecError(sec_status));

    if(!fake)
    {
        sec_status = pFreeCredentialsHandle(&server.cred);
        ok(sec_status == SEC_E_OK, "FreeCredentialsHandle(server) returned %s\n",
            getSecError(sec_status));
    }

    sec_status = pFreeCredentialsHandle(&client.cred);
    ok(sec_status == SEC_E_OK, "FreeCredentialsHandle(client) returned %s\n",
            getSecError(sec_status));
}