#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * stack; } ;
typedef  TYPE_3__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  disp; } ;
struct TYPE_9__ {size_t off; TYPE_1__ idref; } ;
struct TYPE_11__ {int type; TYPE_2__ u; } ;
typedef  TYPE_4__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  EXPRVAL_IDREF 129 
#define  EXPRVAL_STACK_REF 128 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disp_propget (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exprval_propget(script_ctx_t *ctx, exprval_t *ref, jsval_t *r)
{
    switch(ref->type) {
    case EXPRVAL_STACK_REF:
        return jsval_copy(ctx->stack[ref->u.off], r);
    case EXPRVAL_IDREF:
        return disp_propget(ctx, ref->u.idref.disp, ref->u.idref.id, r);
    default:
        assert(0);
        return E_FAIL;
    }
}