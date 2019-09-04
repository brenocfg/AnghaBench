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
 int /*<<< orphan*/  JS_E_OBJECT_EXPECTED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int const) ; 
 int /*<<< orphan*/  exprval_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprval_propput (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprval_release (int /*<<< orphan*/ *) ; 
 int get_op_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (double) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop_exprval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT interp_preinc(script_ctx_t *ctx)
{
    const int arg = get_op_int(ctx, 0);
    exprval_t ref;
    double ret;
    jsval_t v;
    HRESULT hres;

    TRACE("%d\n", arg);

    if(!stack_pop_exprval(ctx, &ref))
        return throw_type_error(ctx, JS_E_OBJECT_EXPECTED, NULL);

    hres = exprval_propget(ctx, &ref, &v);
    if(SUCCEEDED(hres)) {
        double n;

        hres = to_number(ctx, v, &n);
        jsval_release(v);
        if(SUCCEEDED(hres)) {
            ret = n+(double)arg;
            hres = exprval_propput(ctx, &ref, jsval_number(ret));
        }
    }
    exprval_release(&ref);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, jsval_number(ret));
}