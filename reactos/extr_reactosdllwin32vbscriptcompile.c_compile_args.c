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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ expression_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static HRESULT compile_args(compile_ctx_t *ctx, expression_t *args, unsigned *ret)
{
    unsigned arg_cnt = 0;
    HRESULT hres;

    while(args) {
        hres = compile_expression(ctx, args);
        if(FAILED(hres))
            return hres;

        arg_cnt++;
        args = args->next;
    }

    *ret = arg_cnt;
    return S_OK;
}