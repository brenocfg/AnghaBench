#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* subexpr; } ;
typedef  TYPE_3__ unary_expression_t ;
struct TYPE_13__ {TYPE_1__* args; } ;
typedef  TYPE_4__ member_expression_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_14__ {TYPE_4__* expr; int /*<<< orphan*/  is_strict; } ;
typedef  TYPE_5__ call_statement_t ;
struct TYPE_15__ {int /*<<< orphan*/  right; TYPE_2__* left; } ;
typedef  TYPE_6__ binary_expression_t ;
struct TYPE_11__ {scalar_t__ type; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ EXPR_BRACKETS ; 
 scalar_t__ EXPR_EQUAL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  compile_assignment (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_member_expression (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_catch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_call_statement(compile_ctx_t *ctx, call_statement_t *stat)
{
    HRESULT hres;

    /* It's challenging for parser to distinguish parameterized assignment with one argument from call
     * with equality expression argument, so we do it in compiler. */
    if(!stat->is_strict && stat->expr->args && !stat->expr->args->next && stat->expr->args->type == EXPR_EQUAL) {
        binary_expression_t *eqexpr = (binary_expression_t*)stat->expr->args;

        if(eqexpr->left->type == EXPR_BRACKETS) {
            member_expression_t new_member = *stat->expr;

            WARN("converting call expr to assign expr\n");

            new_member.args = ((unary_expression_t*)eqexpr->left)->subexpr;
            return compile_assignment(ctx, &new_member, eqexpr->right, FALSE);
        }
    }

    hres = compile_member_expression(ctx, stat->expr, FALSE);
    if(FAILED(hres))
        return hres;

    if(!emit_catch(ctx, 0))
        return E_OUTOFMEMORY;

    return S_OK;
}