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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  default_valueW ; 
 int /*<<< orphan*/ * jsstr_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Object_get_value(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t *r)
{
    jsstr_t *ret;

    TRACE("\n");

    ret = jsstr_alloc(default_valueW);
    if(!ret)
        return E_OUTOFMEMORY;

    *r = jsval_string(ret);
    return S_OK;
}