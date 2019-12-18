#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lval; } ;
struct TYPE_7__ {int type; int cval; void* is_const; TYPE_1__ u; struct TYPE_7__* ref; } ;
typedef  TYPE_2__ expr_t ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  EXPR_LOGNOT 131 
#define  EXPR_NEG 130 
#define  EXPR_NOT 129 
#define  EXPR_POS 128 
 void* FALSE ; 
 void* TRUE ; 
 TYPE_2__* xmalloc (int) ; 

expr_t *make_expr1(enum expr_type type, expr_t *expr)
{
    expr_t *e;
    e = xmalloc(sizeof(expr_t));
    e->type = type;
    e->ref = expr;
    e->u.lval = 0;
    e->is_const = FALSE;
    /* check for compile-time optimization */
    if (expr->is_const)
    {
        e->is_const = TRUE;
        switch (type)
        {
        case EXPR_LOGNOT:
            e->cval = !expr->cval;
            break;
        case EXPR_POS:
            e->cval = +expr->cval;
            break;
        case EXPR_NEG:
            e->cval = -expr->cval;
            break;
        case EXPR_NOT:
            e->cval = ~expr->cval;
            break;
        default:
            e->is_const = FALSE;
            break;
        }
    }
    return e;
}