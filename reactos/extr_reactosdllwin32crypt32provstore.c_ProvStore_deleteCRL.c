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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  context_t ;
struct TYPE_7__ {TYPE_4__* memStore; int /*<<< orphan*/  hStoreProv; scalar_t__ (* provDeleteCrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ WINE_PROVIDERSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_8__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {scalar_t__ (* delete ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_2__ crls; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  context_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL ProvStore_deleteCRL(WINECRYPT_CERTSTORE *store, context_t *crl)
{
    WINE_PROVIDERSTORE *ps = (WINE_PROVIDERSTORE*)store;
    BOOL ret = TRUE;

    TRACE("(%p, %p)\n", store, crl);

    if (ps->provDeleteCrl)
        ret = ps->provDeleteCrl(ps->hStoreProv, context_ptr(crl), 0);
    if (ret)
        ret = ps->memStore->vtbl->crls.delete(ps->memStore, crl);
    return ret;
}