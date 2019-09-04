#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * v; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_4__ ref_t ;
struct TYPE_14__ {TYPE_3__* instr; } ;
typedef  TYPE_5__ exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_11__ {int /*<<< orphan*/  bstr; } ;
struct TYPE_12__ {TYPE_2__ arg1; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ REF_VAR ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  VBDISP_LET ; 
 int /*<<< orphan*/  VarAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_identifier (TYPE_5__*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stack_top (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_incc(exec_ctx_t *ctx)
{
    const BSTR ident = ctx->instr->arg1.bstr;
    VARIANT v;
    ref_t ref;
    HRESULT hres;

    TRACE("\n");

    hres = lookup_identifier(ctx, ident, VBDISP_LET, &ref);
    if(FAILED(hres))
        return hres;

    if(ref.type != REF_VAR) {
        FIXME("ref.type is not REF_VAR\n");
        return E_FAIL;
    }

    hres = VarAdd(stack_top(ctx, 0), ref.u.v, &v);
    if(FAILED(hres))
        return hres;

    VariantClear(ref.u.v);
    *ref.u.v = v;
    return S_OK;
}