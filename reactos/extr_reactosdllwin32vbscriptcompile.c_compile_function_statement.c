#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* func_decl; } ;
typedef  TYPE_3__ function_statement_t ;
struct TYPE_10__ {TYPE_2__* func_decls; TYPE_1__* code; int /*<<< orphan*/ * func; } ;
typedef  TYPE_4__ compile_ctx_t ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  main_code; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT compile_function_statement(compile_ctx_t *ctx, function_statement_t *stat)
{
    if(ctx->func != &ctx->code->main_code) {
        FIXME("Function is not in the global code\n");
        return E_FAIL;
    }

    stat->func_decl->next = ctx->func_decls;
    ctx->func_decls = stat->func_decl;
    return S_OK;
}