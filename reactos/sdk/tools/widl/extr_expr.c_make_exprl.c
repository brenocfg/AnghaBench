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
struct TYPE_5__ {int lval; } ;
struct TYPE_6__ {int type; int cval; int /*<<< orphan*/  is_const; TYPE_1__ u; int /*<<< orphan*/ * ref; } ;
typedef  TYPE_2__ expr_t ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
 int EXPR_HEXNUM ; 
 int EXPR_NUM ; 
 int EXPR_TRUEFALSE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* xmalloc (int) ; 

expr_t *make_exprl(enum expr_type type, int val)
{
    expr_t *e = xmalloc(sizeof(expr_t));
    e->type = type;
    e->ref = NULL;
    e->u.lval = val;
    e->is_const = FALSE;
    /* check for numeric constant */
    if (type == EXPR_NUM || type == EXPR_HEXNUM || type == EXPR_TRUEFALSE)
    {
        /* make sure true/false value is valid */
        assert(type != EXPR_TRUEFALSE || val == 0 || val == 1);
        e->is_const = TRUE;
        e->cval = val;
    }
    return e;
}