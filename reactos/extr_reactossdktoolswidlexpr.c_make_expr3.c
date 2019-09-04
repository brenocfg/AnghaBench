#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* ext; } ;
struct TYPE_9__ {int type; void* is_const; int /*<<< orphan*/  cval; struct TYPE_9__* ext2; TYPE_1__ u; struct TYPE_9__* ref; } ;
typedef  TYPE_2__ expr_t ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  EXPR_COND 128 
 void* FALSE ; 
 void* TRUE ; 
 TYPE_2__* xmalloc (int) ; 

expr_t *make_expr3(enum expr_type type, expr_t *expr1, expr_t *expr2, expr_t *expr3)
{
    expr_t *e;
    e = xmalloc(sizeof(expr_t));
    e->type = type;
    e->ref = expr1;
    e->u.ext = expr2;
    e->ext2 = expr3;
    e->is_const = FALSE;
    /* check for compile-time optimization */
    if (expr1->is_const && expr2->is_const && expr3->is_const)
    {
        e->is_const = TRUE;
        switch (type)
        {
        case EXPR_COND:
            e->cval = expr1->cval ? expr2->cval : expr3->cval;
            break;
        default:
            e->is_const = FALSE;
            break;
        }
    }
    return e;
}