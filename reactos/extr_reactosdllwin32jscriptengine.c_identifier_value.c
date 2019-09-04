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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_5__ {int /*<<< orphan*/  hres; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ EXPRVAL_INVALID ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprval_to_value (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  identifier_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT identifier_value(script_ctx_t *ctx, BSTR identifier)
{
    exprval_t exprval;
    jsval_t v;
    HRESULT hres;

    hres = identifier_eval(ctx, identifier, &exprval);
    if(FAILED(hres))
        return hres;

    if(exprval.type == EXPRVAL_INVALID)
        return throw_type_error(ctx, exprval.u.hres, identifier);

    hres = exprval_to_value(ctx, &exprval, &v);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, v);
}