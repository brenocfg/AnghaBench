#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* expression; } ;
typedef  TYPE_1__ unary_expression_t ;
struct TYPE_16__ {TYPE_3__* property_list; } ;
typedef  TYPE_2__ property_value_expression_t ;
struct TYPE_17__ {TYPE_5__* value; struct TYPE_17__* next; } ;
typedef  TYPE_3__ property_definition_t ;
struct TYPE_18__ {TYPE_5__* expression; } ;
typedef  TYPE_4__ member_expression_t ;
typedef  int /*<<< orphan*/  function_expression_t ;
struct TYPE_19__ {int type; } ;
typedef  TYPE_5__ expression_t ;
struct TYPE_20__ {TYPE_5__* false_expression; TYPE_5__* true_expression; TYPE_5__* expression; } ;
typedef  TYPE_6__ conditional_expression_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_21__ {TYPE_11__* argument_list; TYPE_5__* expression; } ;
typedef  TYPE_7__ call_expression_t ;
struct TYPE_22__ {TYPE_5__* expression2; TYPE_5__* expression1; } ;
typedef  TYPE_8__ binary_expression_t ;
struct TYPE_23__ {TYPE_10__* element_list; } ;
typedef  TYPE_9__ array_literal_expression_t ;
struct TYPE_13__ {TYPE_5__* expr; struct TYPE_13__* next; } ;
typedef  TYPE_10__ array_element_t ;
struct TYPE_14__ {TYPE_5__* expr; struct TYPE_14__* next; } ;
typedef  TYPE_11__ argument_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
#define  EXPR_ADD 185 
#define  EXPR_AND 184 
#define  EXPR_ARRAY 183 
#define  EXPR_ARRAYLIT 182 
#define  EXPR_ASSIGN 181 
#define  EXPR_ASSIGNADD 180 
#define  EXPR_ASSIGNAND 179 
#define  EXPR_ASSIGNDIV 178 
#define  EXPR_ASSIGNLSHIFT 177 
#define  EXPR_ASSIGNMOD 176 
#define  EXPR_ASSIGNMUL 175 
#define  EXPR_ASSIGNOR 174 
#define  EXPR_ASSIGNRRSHIFT 173 
#define  EXPR_ASSIGNRSHIFT 172 
#define  EXPR_ASSIGNSUB 171 
#define  EXPR_ASSIGNXOR 170 
#define  EXPR_BAND 169 
#define  EXPR_BITNEG 168 
#define  EXPR_BOR 167 
#define  EXPR_BXOR 166 
#define  EXPR_CALL 165 
#define  EXPR_COMMA 164 
#define  EXPR_COND 163 
#define  EXPR_DELETE 162 
#define  EXPR_DIV 161 
#define  EXPR_EQ 160 
#define  EXPR_EQEQ 159 
#define  EXPR_FUNC 158 
#define  EXPR_GREATER 157 
#define  EXPR_GREATEREQ 156 
#define  EXPR_IDENT 155 
#define  EXPR_IN 154 
#define  EXPR_INSTANCEOF 153 
#define  EXPR_LESS 152 
#define  EXPR_LESSEQ 151 
#define  EXPR_LITERAL 150 
#define  EXPR_LOGNEG 149 
#define  EXPR_LSHIFT 148 
#define  EXPR_MEMBER 147 
#define  EXPR_MINUS 146 
#define  EXPR_MOD 145 
#define  EXPR_MUL 144 
#define  EXPR_NEW 143 
#define  EXPR_NOTEQ 142 
#define  EXPR_NOTEQEQ 141 
#define  EXPR_OR 140 
#define  EXPR_PLUS 139 
#define  EXPR_POSTDEC 138 
#define  EXPR_POSTINC 137 
#define  EXPR_PREDEC 136 
#define  EXPR_PREINC 135 
#define  EXPR_PROPVAL 134 
#define  EXPR_RRSHIFT 133 
#define  EXPR_RSHIFT 132 
#define  EXPR_SUB 131 
#define  EXPR_THIS 130 
#define  EXPR_TYPEOF 129 
#define  EXPR_VOID 128 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  visit_function_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT visit_expression(compiler_ctx_t *ctx, expression_t *expr)
{
    HRESULT hres = S_OK;

    switch(expr->type) {
    case EXPR_ADD:
    case EXPR_AND:
    case EXPR_ARRAY:
    case EXPR_ASSIGN:
    case EXPR_ASSIGNADD:
    case EXPR_ASSIGNAND:
    case EXPR_ASSIGNSUB:
    case EXPR_ASSIGNMUL:
    case EXPR_ASSIGNDIV:
    case EXPR_ASSIGNMOD:
    case EXPR_ASSIGNOR:
    case EXPR_ASSIGNLSHIFT:
    case EXPR_ASSIGNRSHIFT:
    case EXPR_ASSIGNRRSHIFT:
    case EXPR_ASSIGNXOR:
    case EXPR_BAND:
    case EXPR_BOR:
    case EXPR_COMMA:
    case EXPR_DIV:
    case EXPR_EQ:
    case EXPR_EQEQ:
    case EXPR_GREATER:
    case EXPR_GREATEREQ:
    case EXPR_IN:
    case EXPR_INSTANCEOF:
    case EXPR_LESS:
    case EXPR_LESSEQ:
    case EXPR_LSHIFT:
    case EXPR_MOD:
    case EXPR_MUL:
    case EXPR_NOTEQ:
    case EXPR_NOTEQEQ:
    case EXPR_OR:
    case EXPR_RSHIFT:
    case EXPR_RRSHIFT:
    case EXPR_SUB:
    case EXPR_BXOR: {
        binary_expression_t *binary_expr = (binary_expression_t*)expr;

        hres = visit_expression(ctx, binary_expr->expression1);
        if(FAILED(hres))
            return hres;

        hres = visit_expression(ctx, binary_expr->expression2);
        break;
    }
    case EXPR_BITNEG:
    case EXPR_DELETE:
    case EXPR_LOGNEG:
    case EXPR_MINUS:
    case EXPR_PLUS:
    case EXPR_POSTDEC:
    case EXPR_POSTINC:
    case EXPR_PREDEC:
    case EXPR_PREINC:
    case EXPR_TYPEOF:
    case EXPR_VOID:
        hres = visit_expression(ctx, ((unary_expression_t*)expr)->expression);
        break;
    case EXPR_IDENT:
    case EXPR_LITERAL:
    case EXPR_THIS:
        break;
    case EXPR_ARRAYLIT: {
        array_literal_expression_t *array_expr = (array_literal_expression_t*)expr;
        array_element_t *iter;

        for(iter = array_expr->element_list; iter; iter = iter->next) {
            hres = visit_expression(ctx, iter->expr);
            if(FAILED(hres))
                return hres;
        }
        break;
    }
    case EXPR_CALL:
    case EXPR_NEW: {
        call_expression_t *call_expr = (call_expression_t*)expr;
        argument_t *arg;

        hres = visit_expression(ctx, call_expr->expression);
        if(FAILED(hres))
            return hres;

        for(arg = call_expr->argument_list; arg; arg = arg->next) {
            hres = visit_expression(ctx, arg->expr);
            if(FAILED(hres))
                return hres;
        }
        break;
    }
    case EXPR_COND: {
        conditional_expression_t *cond_expr = (conditional_expression_t*)expr;

        hres = visit_expression(ctx, cond_expr->expression);
        if(FAILED(hres))
            return hres;

        hres = visit_expression(ctx, cond_expr->true_expression);
        if(FAILED(hres))
            return hres;

        hres = visit_expression(ctx, cond_expr->false_expression);
        break;
    }
    case EXPR_FUNC:
        hres = visit_function_expression(ctx, (function_expression_t*)expr);
        break;
    case EXPR_MEMBER:
        hres = visit_expression(ctx, ((member_expression_t*)expr)->expression);
        break;
    case EXPR_PROPVAL: {
        property_definition_t *iter;
        for(iter = ((property_value_expression_t*)expr)->property_list; iter; iter = iter->next) {
            hres = visit_expression(ctx, iter->value);
            if(FAILED(hres))
                return hres;
        }
        break;
    }
    DEFAULT_UNREACHABLE;
    }

    return hres;
}