#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  context_t ;
struct TYPE_10__ {int /*<<< orphan*/ * hCertStore; } ;
struct TYPE_11__ {TYPE_3__ ctx; } ;
typedef  TYPE_4__ cert_t ;
struct TYPE_12__ {TYPE_6__* memStore; int /*<<< orphan*/  hStoreProv; scalar_t__ (* provWriteCert ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ WINE_PROVIDERSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_13__ {TYPE_2__* vtbl; } ;
struct TYPE_8__ {scalar_t__ (* addContext ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ;} ;
struct TYPE_9__ {TYPE_1__ certs; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_STORE_PROV_WRITE_ADD_FLAG ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  context_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 

__attribute__((used)) static BOOL ProvStore_addCert(WINECRYPT_CERTSTORE *store, context_t *cert,
 context_t *toReplace, context_t **ppStoreContext, BOOL use_link)
{
    WINE_PROVIDERSTORE *ps = (WINE_PROVIDERSTORE*)store;
    BOOL ret;

    TRACE("(%p, %p, %p, %p)\n", store, cert, toReplace, ppStoreContext);

    if (toReplace)
        ret = ps->memStore->vtbl->certs.addContext(ps->memStore, cert, toReplace,
         ppStoreContext, TRUE);
    else
    {
        ret = TRUE;
        if (ps->provWriteCert)
            ret = ps->provWriteCert(ps->hStoreProv, context_ptr(cert), CERT_STORE_PROV_WRITE_ADD_FLAG);
        if (ret)
            ret = ps->memStore->vtbl->certs.addContext(ps->memStore, cert, NULL,
             ppStoreContext, TRUE);
    }
    /* dirty trick: replace the returned context's hCertStore with
     * store.
     */
    if (ret && ppStoreContext)
        (*(cert_t**)ppStoreContext)->ctx.hCertStore = store;
    return ret;
}