#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  linked; TYPE_1__* vtbl; int /*<<< orphan*/  properties; int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ context_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ContextPropertyList_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Context_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void Context_Free(context_t *context)
{
    TRACE("(%p)\n", context);

    assert(!context->ref);

    if (!context->linked) {
        ContextPropertyList_Free(context->properties);
        context->vtbl->free(context);
    }else {
        Context_Release(context->linked);
    }

    CryptMemFree(context);
}