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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_FUNCTION_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * function_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  function_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Function_toString(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    FunctionInstance *function;
    jsstr_t *str;
    HRESULT hres;

    TRACE("\n");

    if(!(function = function_this(jsthis)))
        return throw_type_error(ctx, JS_E_FUNCTION_EXPECTED, NULL);

    hres = function_to_string(function, &str);
    if(FAILED(hres))
        return hres;

    if(r)
        *r = jsval_string(str);
    else
        jsstr_release(str);
    return S_OK;
}