#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  store_vtbl_t ;
struct TYPE_3__ {int ref; int /*<<< orphan*/ * properties; int /*<<< orphan*/  const* vtbl; int /*<<< orphan*/  dwOpenFlags; int /*<<< orphan*/  type; int /*<<< orphan*/  dwMagic; } ;
typedef  TYPE_1__ WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CertStoreType ;

/* Variables and functions */
 int /*<<< orphan*/  WINE_CRYPTCERTSTORE_MAGIC ; 

void CRYPT_InitStore(WINECRYPT_CERTSTORE *store, DWORD dwFlags, CertStoreType type, const store_vtbl_t *vtbl)
{
    store->ref = 1;
    store->dwMagic = WINE_CRYPTCERTSTORE_MAGIC;
    store->type = type;
    store->dwOpenFlags = dwFlags;
    store->vtbl = vtbl;
    store->properties = NULL;
}