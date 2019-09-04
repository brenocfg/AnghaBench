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
struct TYPE_4__ {int /*<<< orphan*/  grbitEnabledProtocols; } ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_1__ SCHANNEL_CRED ;
typedef  int /*<<< orphan*/  CredHandle ;

/* Variables and functions */
 scalar_t__ AcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ QueryCredentialsAttributesA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECPKG_ATTR_SUPPORTED_ALGS ; 
 int /*<<< orphan*/  SECPKG_ATTR_SUPPORTED_PROTOCOLS ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 scalar_t__ SEC_E_INTERNAL_ERROR ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  SP_PROT_TLS1_CLIENT ; 
 int /*<<< orphan*/  init_cred (TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_supported_algs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_supported_protocols (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unisp_name_a ; 

__attribute__((used)) static void test_cread_attrs(void)
{
    SCHANNEL_CRED schannel_cred;
    SECURITY_STATUS status;
    CredHandle cred;

    status = AcquireCredentialsHandleA(NULL, unisp_name_a, SECPKG_CRED_OUTBOUND,
            NULL, NULL, NULL, NULL, &cred, NULL);
    ok(status == SEC_E_OK, "AcquireCredentialsHandleA failed: %x\n", status);

    test_supported_protocols(&cred, 0);
    test_supported_algs(&cred);

    status = QueryCredentialsAttributesA(&cred, SECPKG_ATTR_SUPPORTED_PROTOCOLS, NULL);
    ok(status == SEC_E_INTERNAL_ERROR, "QueryCredentialsAttributes failed: %08x, expected SEC_E_INTERNAL_ERROR\n", status);

    status = QueryCredentialsAttributesA(&cred, SECPKG_ATTR_SUPPORTED_ALGS, NULL);
    ok(status == SEC_E_INTERNAL_ERROR, "QueryCredentialsAttributes failed: %08x, expected SEC_E_INTERNAL_ERROR\n", status);

    FreeCredentialsHandle(&cred);

    init_cred(&schannel_cred);
    schannel_cred.grbitEnabledProtocols = SP_PROT_TLS1_CLIENT;
    status = AcquireCredentialsHandleA(NULL, unisp_name_a, SECPKG_CRED_OUTBOUND,
            NULL, &schannel_cred, NULL, NULL, &cred, NULL);
    ok(status == SEC_E_OK, "AcquireCredentialsHandleA failed: %x\n", status);

    test_supported_protocols(&cred, SP_PROT_TLS1_CLIENT);
    test_supported_algs(&cred);

    FreeCredentialsHandle(&cred);
}