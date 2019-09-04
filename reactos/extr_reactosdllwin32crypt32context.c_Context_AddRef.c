#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* store; int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ context_t ;
struct TYPE_8__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* addref ) (TYPE_3__*) ;} ;
typedef  int LONG ;

/* Variables and functions */
 int InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void Context_AddRef(context_t *context)
{
    LONG ref = InterlockedIncrement(&context->ref);

    TRACE("(%p) ref=%d\n", context, context->ref);

    if(ref == 1) {
        /* This is the first external (non-store) reference. Increase store ref cnt. */
        context->store->vtbl->addref(context->store);
    }
}