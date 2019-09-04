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
struct TYPE_4__ {scalar_t__ dwMagic; scalar_t__ properties; } ;
typedef  TYPE_1__ WINECRYPT_CERTSTORE ;

/* Variables and functions */
 int /*<<< orphan*/  ContextPropertyList_Free (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_1__*) ; 

void CRYPT_FreeStore(WINECRYPT_CERTSTORE *store)
{
    if (store->properties)
        ContextPropertyList_Free(store->properties);
    store->dwMagic = 0;
    CryptMemFree(store);
}