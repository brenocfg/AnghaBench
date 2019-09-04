#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_12__ {TYPE_2__ u; TYPE_1__* vtbl; } ;
typedef  TYPE_3__ context_t ;
typedef  int /*<<< orphan*/  WINE_STORE_LIST_ENTRY ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_4__ WINE_COLLECTIONSTORE ;
struct TYPE_10__ {TYPE_3__* (* clone ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static context_t *CRYPT_CollectionCreateContextFromChild(WINE_COLLECTIONSTORE *store,
 WINE_STORE_LIST_ENTRY *storeEntry, context_t *child)
{
    context_t *ret;

    ret = child->vtbl->clone(child, &store->hdr, TRUE);
    if (!ret)
        return NULL;

    ret->u.ptr = storeEntry;
    return ret;
}