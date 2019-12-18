#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ stgclass; int /*<<< orphan*/ * type; } ;
typedef  TYPE_2__ var_t ;
typedef  int /*<<< orphan*/  type_t ;
struct TYPE_9__ {int /*<<< orphan*/ * tref; } ;
struct TYPE_11__ {int type; int cval; void* is_const; TYPE_1__ u; struct TYPE_11__* ref; } ;
typedef  TYPE_3__ expr_t ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
 int EXPR_CAST ; 
 int EXPR_SIZEOF ; 
 void* FALSE ; 
 scalar_t__ STG_NONE ; 
 scalar_t__ STG_REGISTER ; 
 void* TRUE ; 
 int /*<<< orphan*/  error_loc (char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ is_float_type (int /*<<< orphan*/ *) ; 
 scalar_t__ is_integer_type (int /*<<< orphan*/ *) ; 
 scalar_t__ is_signed_integer_type (int /*<<< orphan*/ *) ; 
 int type_memsize (int /*<<< orphan*/ *) ; 
 TYPE_3__* xmalloc (int) ; 

expr_t *make_exprt(enum expr_type type, var_t *var, expr_t *expr)
{
    expr_t *e;
    type_t *tref;

    if (var->stgclass != STG_NONE && var->stgclass != STG_REGISTER)
        error_loc("invalid storage class for type expression\n");

    tref = var->type;

    e = xmalloc(sizeof(expr_t));
    e->type = type;
    e->ref = expr;
    e->u.tref = tref;
    e->is_const = FALSE;
    if (type == EXPR_SIZEOF)
    {
        /* only do this for types that should be the same on all platforms */
        if (is_integer_type(tref) || is_float_type(tref))
        {
            e->is_const = TRUE;
            e->cval = type_memsize(tref);
        }
    }
    /* check for cast of constant expression */
    if (type == EXPR_CAST && expr->is_const)
    {
        if (is_integer_type(tref))
        {
            unsigned int cast_type_bits = type_memsize(tref) * 8;
            unsigned int cast_mask;

            e->is_const = TRUE;
            if (is_signed_integer_type(tref))
            {
                cast_mask = (1u << (cast_type_bits - 1)) - 1;
                if (expr->cval & (1u << (cast_type_bits - 1)))
                    e->cval = -((-expr->cval) & cast_mask);
                else
                    e->cval = expr->cval & cast_mask;
            }
            else
            {
                /* calculate ((1 << cast_type_bits) - 1) avoiding overflow */
                cast_mask = ((1u << (cast_type_bits - 1)) - 1) |
                            1u << (cast_type_bits - 1);
                e->cval = expr->cval & cast_mask;
            }
        }
        else
        {
            e->is_const = TRUE;
            e->cval = expr->cval;
        }
    }
    free(var);
    return e;
}