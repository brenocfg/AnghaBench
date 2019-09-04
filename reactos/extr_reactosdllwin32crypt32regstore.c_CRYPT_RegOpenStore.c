#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  provInfo ;
struct TYPE_10__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {int dwOpenFlags; int /*<<< orphan*/  dirty; int /*<<< orphan*/ * memStore; scalar_t__ key; int /*<<< orphan*/  ctlsToDelete; int /*<<< orphan*/  crlsToDelete; int /*<<< orphan*/  certsToDelete; TYPE_4__ cs; } ;
typedef  TYPE_2__ WINE_REGSTOREINFO ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_9__ {int cbSize; TYPE_2__* hStoreProv; int /*<<< orphan*/  rgpvStoreProvFunc; int /*<<< orphan*/  cStoreProvFunc; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  LPHANDLE ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ HCRYPTPROV ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;
typedef  TYPE_3__ CERT_STORE_PROV_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int CERT_STORE_DELETE_FLAG ; 
 int CERT_STORE_NO_CRYPT_RELEASE_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int CERT_STORE_READONLY_FLAG ; 
 int /*<<< orphan*/  CRLsW ; 
 int /*<<< orphan*/ * CRYPT_ProvCreateStore (int,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  CRYPT_RegReadFromReg (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CTLsW ; 
 int /*<<< orphan*/ * CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertsW ; 
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DuplicateHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int RegDeleteTreeW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regProvFuncs ; 

WINECRYPT_CERTSTORE *CRYPT_RegOpenStore(HCRYPTPROV hCryptProv, DWORD dwFlags,
 const void *pvPara)
{
    WINECRYPT_CERTSTORE *store = NULL;

    TRACE("(%ld, %08x, %p)\n", hCryptProv, dwFlags, pvPara);

    if (dwFlags & CERT_STORE_DELETE_FLAG)
    {
        DWORD rc = RegDeleteTreeW((HKEY)pvPara, CertsW);

        if (rc == ERROR_SUCCESS || rc == ERROR_NO_MORE_ITEMS)
            rc = RegDeleteTreeW((HKEY)pvPara, CRLsW);
        if (rc == ERROR_SUCCESS || rc == ERROR_NO_MORE_ITEMS)
            rc = RegDeleteTreeW((HKEY)pvPara, CTLsW);
        if (rc == ERROR_NO_MORE_ITEMS)
            rc = ERROR_SUCCESS;
        SetLastError(rc);
    }
    else
    {
        HKEY key;

        if (DuplicateHandle(GetCurrentProcess(), (HANDLE)pvPara,
         GetCurrentProcess(), (LPHANDLE)&key,
         dwFlags & CERT_STORE_READONLY_FLAG ? KEY_READ : KEY_ALL_ACCESS,
         TRUE, 0))
        {
            WINECRYPT_CERTSTORE *memStore;

            memStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, hCryptProv,
             CERT_STORE_CREATE_NEW_FLAG, NULL);
            if (memStore)
            {
                WINE_REGSTOREINFO *regInfo = CryptMemAlloc(
                 sizeof(WINE_REGSTOREINFO));

                if (regInfo)
                {
                    CERT_STORE_PROV_INFO provInfo = { 0 };

                    regInfo->dwOpenFlags = dwFlags;
                    regInfo->memStore = memStore;
                    regInfo->key = key;
                    InitializeCriticalSection(&regInfo->cs);
                    regInfo->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": PWINE_REGSTOREINFO->cs");
                    list_init(&regInfo->certsToDelete);
                    list_init(&regInfo->crlsToDelete);
                    list_init(&regInfo->ctlsToDelete);
                    CRYPT_RegReadFromReg(regInfo->key, regInfo->memStore);
                    regInfo->dirty = FALSE;
                    provInfo.cbSize = sizeof(provInfo);
                    provInfo.cStoreProvFunc = ARRAY_SIZE(regProvFuncs);
                    provInfo.rgpvStoreProvFunc = regProvFuncs;
                    provInfo.hStoreProv = regInfo;
                    store = CRYPT_ProvCreateStore(dwFlags, memStore, &provInfo);
                    /* Reg store doesn't need crypto provider, so close it */
                    if (hCryptProv &&
                     !(dwFlags & CERT_STORE_NO_CRYPT_RELEASE_FLAG))
                        CryptReleaseContext(hCryptProv, 0);
                }
            }
        }
    }
    TRACE("returning %p\n", store);
    return store;
}