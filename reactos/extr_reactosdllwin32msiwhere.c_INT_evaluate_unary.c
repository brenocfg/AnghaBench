#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct complex_expr {int op; TYPE_2__* left; } ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  column; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
#define  OP_ISNULL 129 
#define  OP_NOTNULL 128 
 scalar_t__ expr_fetch_value (int /*<<< orphan*/ *,scalar_t__ const*,scalar_t__*) ; 

__attribute__((used)) static UINT INT_evaluate_unary( MSIWHEREVIEW *wv, const UINT rows[],
                                const struct complex_expr *expr, INT *val, MSIRECORD *record )
{
    UINT r;
    UINT lval;

    r = expr_fetch_value(&expr->left->u.column, rows, &lval);
    if(r != ERROR_SUCCESS)
        return r;

    switch( expr->op )
    {
    case OP_ISNULL:
        *val = !lval;
        break;
    case OP_NOTNULL:
        *val = lval;
        break;
    default:
        ERR("Unknown operator %d\n", expr->op );
        return ERROR_FUNCTION_FAILED;
    }
    return ERROR_SUCCESS;
}