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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* code; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int param_cnt; int /*<<< orphan*/ * params; } ;
struct TYPE_8__ {TYPE_1__ global_code; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * compiler_alloc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  parse_arguments (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HRESULT compile_arguments(compiler_ctx_t *ctx, const WCHAR *args)
{
    HRESULT hres;

    hres = parse_arguments(ctx, args, NULL, &ctx->code->global_code.param_cnt);
    if(FAILED(hres))
        return hres;

    ctx->code->global_code.params = compiler_alloc(ctx->code,
            ctx->code->global_code.param_cnt * sizeof(*ctx->code->global_code.params));
    if(!ctx->code->global_code.params)
        return E_OUTOFMEMORY;

    return parse_arguments(ctx, args, ctx->code->global_code.params, NULL);
}