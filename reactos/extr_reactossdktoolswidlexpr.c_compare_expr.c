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
struct TYPE_5__ {int lval; int dval; int /*<<< orphan*/  tref; TYPE_2__* ext; int /*<<< orphan*/  sval; } ;
struct TYPE_6__ {int type; TYPE_1__ u; struct TYPE_6__* ref; struct TYPE_6__* ext2; } ;
typedef  TYPE_2__ expr_t ;

/* Variables and functions */
#define  EXPR_ADD 165 
#define  EXPR_ADDRESSOF 164 
#define  EXPR_AND 163 
#define  EXPR_ARRAY 162 
#define  EXPR_CAST 161 
#define  EXPR_CHARCONST 160 
#define  EXPR_COND 159 
#define  EXPR_DIV 158 
#define  EXPR_DOUBLE 157 
#define  EXPR_EQUALITY 156 
#define  EXPR_GTR 155 
#define  EXPR_GTREQL 154 
#define  EXPR_HEXNUM 153 
#define  EXPR_IDENTIFIER 152 
#define  EXPR_INEQUALITY 151 
#define  EXPR_LESS 150 
#define  EXPR_LESSEQL 149 
#define  EXPR_LOGAND 148 
#define  EXPR_LOGNOT 147 
#define  EXPR_LOGOR 146 
#define  EXPR_MEMBER 145 
#define  EXPR_MOD 144 
#define  EXPR_MUL 143 
#define  EXPR_NEG 142 
#define  EXPR_NOT 141 
#define  EXPR_NUM 140 
#define  EXPR_OR 139 
#define  EXPR_POS 138 
#define  EXPR_PPTR 137 
#define  EXPR_SHL 136 
#define  EXPR_SHR 135 
#define  EXPR_SIZEOF 134 
#define  EXPR_STRLIT 133 
#define  EXPR_SUB 132 
#define  EXPR_TRUEFALSE 131 
#define  EXPR_VOID 130 
#define  EXPR_WSTRLIT 129 
#define  EXPR_XOR 128 
 int compare_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int compare_expr(const expr_t *a, const expr_t *b)
{
    int ret;

    if (a->type != b->type)
        return a->type - b->type;

    switch (a->type)
    {
        case EXPR_NUM:
        case EXPR_HEXNUM:
        case EXPR_TRUEFALSE:
            return a->u.lval - b->u.lval;
        case EXPR_DOUBLE:
            return a->u.dval - b->u.dval;
        case EXPR_IDENTIFIER:
        case EXPR_STRLIT:
        case EXPR_WSTRLIT:
        case EXPR_CHARCONST:
            return strcmp(a->u.sval, b->u.sval);
        case EXPR_COND:
            ret = compare_expr(a->ref, b->ref);
            if (ret != 0)
                return ret;
            ret = compare_expr(a->u.ext, b->u.ext);
            if (ret != 0)
                return ret;
            return compare_expr(a->ext2, b->ext2);
        case EXPR_OR:
        case EXPR_AND:
        case EXPR_ADD:
        case EXPR_SUB:
        case EXPR_MOD:
        case EXPR_MUL:
        case EXPR_DIV:
        case EXPR_SHL:
        case EXPR_SHR:
        case EXPR_MEMBER:
        case EXPR_ARRAY:
        case EXPR_LOGOR:
        case EXPR_LOGAND:
        case EXPR_XOR:
        case EXPR_EQUALITY:
        case EXPR_INEQUALITY:
        case EXPR_GTR:
        case EXPR_LESS:
        case EXPR_GTREQL:
        case EXPR_LESSEQL:
            ret = compare_expr(a->ref, b->ref);
            if (ret != 0)
                return ret;
            return compare_expr(a->u.ext, b->u.ext);
        case EXPR_CAST:
            ret = compare_type(a->u.tref, b->u.tref);
            if (ret != 0)
                return ret;
            /* Fall through.  */
        case EXPR_NOT:
        case EXPR_NEG:
        case EXPR_PPTR:
        case EXPR_ADDRESSOF:
        case EXPR_LOGNOT:
        case EXPR_POS:
            return compare_expr(a->ref, b->ref);
        case EXPR_SIZEOF:
            return compare_type(a->u.tref, b->u.tref);
        case EXPR_VOID:
            return 0;
    }
    return -1;
}