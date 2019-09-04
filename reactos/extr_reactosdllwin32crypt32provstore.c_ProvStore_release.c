#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {int dwStoreProvFlags; TYPE_5__ hdr; TYPE_3__* memStore; int /*<<< orphan*/  hStoreProv; int /*<<< orphan*/  (* provCloseStore ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ WINE_PROVIDERSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_8__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CERT_STORE_PROV_EXTERNAL_FLAG ; 
 int /*<<< orphan*/  CRYPT_FreeStore (TYPE_5__*) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD ProvStore_release(WINECRYPT_CERTSTORE *cert_store, DWORD flags)
{
    WINE_PROVIDERSTORE *store = (WINE_PROVIDERSTORE*)cert_store;
    LONG ref;

    if(flags)
        FIXME("Unimplemented flags %x\n", flags);

    ref = InterlockedDecrement(&store->hdr.ref);
    TRACE("(%p) ref=%d\n", store, ref);

    if(ref)
        return ERROR_SUCCESS;

    if (store->provCloseStore)
        store->provCloseStore(store->hStoreProv, flags);
    if (!(store->dwStoreProvFlags & CERT_STORE_PROV_EXTERNAL_FLAG))
        store->memStore->vtbl->release(store->memStore, flags);
    CRYPT_FreeStore(&store->hdr);
    return ERROR_SUCCESS;
}