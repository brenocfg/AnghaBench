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
struct TYPE_7__ {int /*<<< orphan*/  stores; TYPE_4__ cs; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_2__ WINE_COLLECTIONSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int CERT_STORE_DELETE_FLAG ; 
 int /*<<< orphan*/  CRYPT_InitStore (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CollectionStoreVtbl ; 
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StoreTypeCollection ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

WINECRYPT_CERTSTORE *CRYPT_CollectionOpenStore(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    WINE_COLLECTIONSTORE *store;

    if (dwFlags & CERT_STORE_DELETE_FLAG)
    {
        SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
        store = NULL;
    }
    else
    {
        store = CryptMemAlloc(sizeof(WINE_COLLECTIONSTORE));
        if (store)
        {
            memset(store, 0, sizeof(WINE_COLLECTIONSTORE));
            CRYPT_InitStore(&store->hdr, dwFlags, StoreTypeCollection, &CollectionStoreVtbl);
            InitializeCriticalSection(&store->cs);
            store->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": PWINE_COLLECTIONSTORE->cs");
            list_init(&store->stores);
        }
    }
    return (WINECRYPT_CERTSTORE*)store;
}