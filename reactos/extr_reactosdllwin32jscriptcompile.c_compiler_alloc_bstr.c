#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* code; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {size_t bstr_cnt; int /*<<< orphan*/ ** bstr_pool; } ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ensure_bstr_slot (TYPE_2__*) ; 

__attribute__((used)) static BSTR compiler_alloc_bstr(compiler_ctx_t *ctx, const WCHAR *str)
{
    if(!ensure_bstr_slot(ctx))
        return NULL;

    ctx->code->bstr_pool[ctx->code->bstr_cnt] = SysAllocString(str);
    if(!ctx->code->bstr_pool[ctx->code->bstr_cnt])
        return NULL;

    return ctx->code->bstr_pool[ctx->code->bstr_cnt++];
}