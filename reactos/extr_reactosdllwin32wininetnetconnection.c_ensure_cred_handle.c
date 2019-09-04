#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int grbitEnabledProtocols; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int grbitProtocol; } ;
typedef  TYPE_1__ SecPkgCred_SupportedProtocols ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_2__ SCHANNEL_CRED ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ AcquireCredentialsHandleW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ QueryCredentialsAttributesA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SCHANNEL_CRED_VERSION ; 
 int /*<<< orphan*/  SECPKG_ATTR_SUPPORTED_PROTOCOLS ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 scalar_t__ SEC_E_OK ; 
 int SP_PROT_TLS1_1PLUS_CLIENT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UNISP_NAME_W ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  compat_cred_handle ; 
 int /*<<< orphan*/  cred_handle ; 
 int cred_handle_initialized ; 
 int have_compat_cred_handle ; 
 int /*<<< orphan*/  init_sechandle_cs ; 

__attribute__((used)) static BOOL ensure_cred_handle(void)
{
    SECURITY_STATUS res = SEC_E_OK;

    EnterCriticalSection(&init_sechandle_cs);

    if(!cred_handle_initialized) {
        SCHANNEL_CRED cred = {SCHANNEL_CRED_VERSION};
        SecPkgCred_SupportedProtocols prots;

        res = AcquireCredentialsHandleW(NULL, (WCHAR*)UNISP_NAME_W, SECPKG_CRED_OUTBOUND, NULL, &cred,
                NULL, NULL, &cred_handle, NULL);
        if(res == SEC_E_OK) {
            res = QueryCredentialsAttributesA(&cred_handle, SECPKG_ATTR_SUPPORTED_PROTOCOLS, &prots);
            if(res != SEC_E_OK || (prots.grbitProtocol & SP_PROT_TLS1_1PLUS_CLIENT)) {
                cred.grbitEnabledProtocols = prots.grbitProtocol & ~SP_PROT_TLS1_1PLUS_CLIENT;
                res = AcquireCredentialsHandleW(NULL, (WCHAR*)UNISP_NAME_W, SECPKG_CRED_OUTBOUND, NULL, &cred,
                       NULL, NULL, &compat_cred_handle, NULL);
                have_compat_cred_handle = res == SEC_E_OK;
            }
        }

        cred_handle_initialized = res == SEC_E_OK;
    }

    LeaveCriticalSection(&init_sechandle_cs);

    if(res != SEC_E_OK) {
        WARN("Failed: %08x\n", res);
        return FALSE;
    }

    return TRUE;
}