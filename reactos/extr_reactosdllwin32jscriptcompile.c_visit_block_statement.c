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
typedef  TYPE_1__ statement_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  visit_statement (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static HRESULT visit_block_statement(compiler_ctx_t *ctx, statement_t *iter)
{
    HRESULT hres;

    while(iter) {
        hres = visit_statement(ctx, iter);
        if(FAILED(hres))
            return hres;

        iter = iter->next;
    }

    return S_OK;
}