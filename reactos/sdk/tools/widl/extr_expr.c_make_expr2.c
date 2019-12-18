#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ext; } ;
struct TYPE_8__ {int type; int cval; void* is_const; TYPE_1__ u; struct TYPE_8__* ref; } ;
typedef  TYPE_2__ expr_t ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  EXPR_ADD 145 
#define  EXPR_AND 144 
#define  EXPR_DIV 143 
#define  EXPR_EQUALITY 142 
#define  EXPR_GTR 141 
#define  EXPR_GTREQL 140 
#define  EXPR_INEQUALITY 139 
#define  EXPR_LESS 138 
#define  EXPR_LESSEQL 137 
#define  EXPR_LOGAND 136 
#define  EXPR_LOGOR 135 
#define  EXPR_MOD 134 
#define  EXPR_MUL 133 
#define  EXPR_OR 132 
#define  EXPR_SHL 131 
#define  EXPR_SHR 130 
#define  EXPR_SUB 129 
#define  EXPR_XOR 128 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  error_loc (char*) ; 
 TYPE_2__* xmalloc (int) ; 

expr_t *make_expr2(enum expr_type type, expr_t *expr1, expr_t *expr2)
{
    expr_t *e;
    e = xmalloc(sizeof(expr_t));
    e->type = type;
    e->ref = expr1;
    e->u.ext = expr2;
    e->is_const = FALSE;
    /* check for compile-time optimization */
    if (expr1->is_const && expr2->is_const)
    {
        e->is_const = TRUE;
        switch (type)
        {
        case EXPR_ADD:
            e->cval = expr1->cval + expr2->cval;
            break;
        case EXPR_SUB:
            e->cval = expr1->cval - expr2->cval;
            break;
        case EXPR_MOD:
            if (expr2->cval == 0)
            {
                error_loc("divide by zero in expression\n");
                e->cval = 0;
            }
            else
                e->cval = expr1->cval % expr2->cval;
            break;
        case EXPR_MUL:
            e->cval = expr1->cval * expr2->cval;
            break;
        case EXPR_DIV:
            if (expr2->cval == 0)
            {
                error_loc("divide by zero in expression\n");
                e->cval = 0;
            }
            else
                e->cval = expr1->cval / expr2->cval;
            break;
        case EXPR_OR:
            e->cval = expr1->cval | expr2->cval;
            break;
        case EXPR_AND:
            e->cval = expr1->cval & expr2->cval;
            break;
        case EXPR_SHL:
            e->cval = expr1->cval << expr2->cval;
            break;
        case EXPR_SHR:
            e->cval = expr1->cval >> expr2->cval;
            break;
        case EXPR_LOGOR:
            e->cval = expr1->cval || expr2->cval;
            break;
        case EXPR_LOGAND:
            e->cval = expr1->cval && expr2->cval;
            break;
        case EXPR_XOR:
            e->cval = expr1->cval ^ expr2->cval;
            break;
        case EXPR_EQUALITY:
            e->cval = expr1->cval == expr2->cval;
            break;
        case EXPR_INEQUALITY:
            e->cval = expr1->cval != expr2->cval;
            break;
        case EXPR_GTR:
            e->cval = expr1->cval > expr2->cval;
            break;
        case EXPR_LESS:
            e->cval = expr1->cval < expr2->cval;
            break;
        case EXPR_GTREQL:
            e->cval = expr1->cval >= expr2->cval;
            break;
        case EXPR_LESSEQL:
            e->cval = expr1->cval <= expr2->cval;
            break;
        default:
            e->is_const = FALSE;
            break;
        }
    }
    return e;
}