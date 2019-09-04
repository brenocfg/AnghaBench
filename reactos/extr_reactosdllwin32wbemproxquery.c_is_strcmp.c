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
struct complex_expr {TYPE_1__* left; TYPE_2__* right; } ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CIM_STRING ; 
 scalar_t__ EXPR_PROPVAL ; 
 scalar_t__ EXPR_SVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_int (scalar_t__) ; 

__attribute__((used)) static inline BOOL is_strcmp( const struct complex_expr *expr, UINT ltype, UINT rtype )
{
    if ((ltype == CIM_STRING || is_int( ltype )) && expr->left->type == EXPR_PROPVAL &&
        expr->right->type == EXPR_SVAL) return TRUE;
    else if ((rtype == CIM_STRING || is_int( rtype )) && expr->right->type == EXPR_PROPVAL &&
             expr->left->type == EXPR_SVAL) return TRUE;
    return FALSE;
}