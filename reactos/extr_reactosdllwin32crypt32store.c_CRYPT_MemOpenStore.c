#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* DebugInfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctls; int /*<<< orphan*/  crls; int /*<<< orphan*/  certs; TYPE_4__ cs; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_2__ WINE_MEMSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  scalar_t__ HCRYPTPROV ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int CERT_STORE_DELETE_FLAG ; 
 int CERT_STORE_NO_CRYPT_RELEASE_FLAG ; 
 int /*<<< orphan*/  CRYPT_InitStore (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  MemStoreVtbl ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StoreTypeMem ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,void const*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_MemOpenStore(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    WINE_MEMSTORE *store;

    TRACE("(%ld, %08x, %p)\n", hCryptProv, dwFlags, pvPara);

    if (dwFlags & CERT_STORE_DELETE_FLAG)
    {
        SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
        store = NULL;
    }
    else
    {
        store = CryptMemAlloc(sizeof(WINE_MEMSTORE));
        if (store)
        {
            memset(store, 0, sizeof(WINE_MEMSTORE));
            CRYPT_InitStore(&store->hdr, dwFlags, StoreTypeMem, &MemStoreVtbl);
            InitializeCriticalSection(&store->cs);
            store->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": ContextList.cs");
            list_init(&store->certs);
            list_init(&store->crls);
            list_init(&store->ctls);
            /* Mem store doesn't need crypto provider, so close it */
            if (hCryptProv && !(dwFlags & CERT_STORE_NO_CRYPT_RELEASE_FLAG))
                CryptReleaseContext(hCryptProv, 0);
        }
    }
    return (WINECRYPT_CERTSTORE*)store;
}