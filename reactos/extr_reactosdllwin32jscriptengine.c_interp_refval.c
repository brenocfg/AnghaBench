#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_ILLEGAL_ASSIGN ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  exprval_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_topn_exprval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_reference_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_refval(script_ctx_t *ctx)
{
    exprval_t ref;
    jsval_t v;
    HRESULT hres;

    TRACE("\n");

    if(!stack_topn_exprval(ctx, 0, &ref))
        return throw_reference_error(ctx, JS_E_ILLEGAL_ASSIGN, NULL);

    hres = exprval_propget(ctx, &ref, &v);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, v);
}