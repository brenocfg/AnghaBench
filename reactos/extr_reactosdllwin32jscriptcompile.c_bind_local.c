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
struct TYPE_6__ {scalar_t__ using_scope; struct TYPE_6__* next; } ;
typedef  TYPE_1__ statement_ctx_t ;
struct TYPE_7__ {int ref; } ;
typedef  TYPE_2__ local_ref_t ;
struct TYPE_8__ {int /*<<< orphan*/  func; TYPE_1__* stat_ctx; } ;
typedef  TYPE_3__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* lookup_local (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL bind_local(compiler_ctx_t *ctx, const WCHAR *identifier, int *ret_ref)
{
    statement_ctx_t *iter;
    local_ref_t *ref;

    for(iter = ctx->stat_ctx; iter; iter = iter->next) {
        if(iter->using_scope)
            return FALSE;
    }

    ref = lookup_local(ctx->func, identifier);
    if(!ref)
        return FALSE;

    *ret_ref = ref->ref;
    return TRUE;
}