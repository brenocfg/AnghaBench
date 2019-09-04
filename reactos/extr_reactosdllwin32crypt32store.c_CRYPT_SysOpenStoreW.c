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
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  scalar_t__ HCRYPTPROV ;
typedef  int /*<<< orphan*/ * HCERTSTORE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG ; 
 int CERT_STORE_CREATE_NEW_FLAG ; 
 int CERT_STORE_NO_CRYPT_RELEASE_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_COLLECTION ; 
 int /*<<< orphan*/  CERT_STORE_PROV_SYSTEM_REGISTRY_W ; 
 int CERT_STORE_READONLY_FLAG ; 
#define  CERT_SYSTEM_STORE_CURRENT_SERVICE 135 
#define  CERT_SYSTEM_STORE_CURRENT_USER 134 
#define  CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY 133 
#define  CERT_SYSTEM_STORE_LOCAL_MACHINE 132 
#define  CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE 131 
#define  CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY 130 
 int CERT_SYSTEM_STORE_LOCATION_MASK ; 
#define  CERT_SYSTEM_STORE_SERVICES 129 
#define  CERT_SYSTEM_STORE_USERS 128 
 int /*<<< orphan*/  CertAddStoreToCollection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (void const*) ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_SysOpenStoreW(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    HCERTSTORE store = 0;
    BOOL ret;

    TRACE("(%ld, %08x, %s)\n", hCryptProv, dwFlags,
     debugstr_w(pvPara));

    if (!pvPara)
    {
        SetLastError(ERROR_FILE_NOT_FOUND);
        return NULL;
    }
    /* This returns a different error than system registry stores if the
     * location is invalid.
     */
    switch (dwFlags & CERT_SYSTEM_STORE_LOCATION_MASK)
    {
    case CERT_SYSTEM_STORE_LOCAL_MACHINE:
    case CERT_SYSTEM_STORE_CURRENT_USER:
    case CERT_SYSTEM_STORE_CURRENT_SERVICE:
    case CERT_SYSTEM_STORE_SERVICES:
    case CERT_SYSTEM_STORE_USERS:
    case CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY:
    case CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY:
    case CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE:
        ret = TRUE;
        break;
    default:
        SetLastError(ERROR_FILE_NOT_FOUND);
        ret = FALSE;
    }
    if (ret)
    {
        HCERTSTORE regStore = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY_W,
         0, 0, dwFlags, pvPara);

        if (regStore)
        {
            store = CertOpenStore(CERT_STORE_PROV_COLLECTION, 0, 0,
             CERT_STORE_CREATE_NEW_FLAG, NULL);
            CertAddStoreToCollection(store, regStore,
             dwFlags & CERT_STORE_READONLY_FLAG ? 0 :
             CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG, 0);
            CertCloseStore(regStore, 0);
            /* CERT_SYSTEM_STORE_CURRENT_USER returns both the HKCU and HKLM
             * stores.
             */
            if ((dwFlags & CERT_SYSTEM_STORE_LOCATION_MASK) ==
             CERT_SYSTEM_STORE_CURRENT_USER)
            {
                dwFlags &= ~CERT_SYSTEM_STORE_CURRENT_USER;
                dwFlags |= CERT_SYSTEM_STORE_LOCAL_MACHINE;
                regStore = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY_W, 0,
                 0, dwFlags, pvPara);
                if (regStore)
                {
                    CertAddStoreToCollection(store, regStore,
                     dwFlags & CERT_STORE_READONLY_FLAG ? 0 :
                     CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG, 0);
                    CertCloseStore(regStore, 0);
                }
            }
            /* System store doesn't need crypto provider, so close it */
            if (hCryptProv && !(dwFlags & CERT_STORE_NO_CRYPT_RELEASE_FLAG))
                CryptReleaseContext(hCryptProv, 0);
        }
    }
    return store;
}