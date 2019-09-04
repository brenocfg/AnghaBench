#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* subexpr; } ;
typedef  TYPE_1__ unary_expression_t ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ string_expression_t ;
typedef  int /*<<< orphan*/  member_expression_t ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ int_expression_t ;
struct TYPE_12__ {int type; } ;
typedef  TYPE_4__ expression_t ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_5__ double_expression_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_6__ bool_expression_t ;
typedef  int /*<<< orphan*/  binary_expression_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_PARAMNOTFOUND ; 
#define  EXPR_ADD 162 
#define  EXPR_AND 161 
#define  EXPR_BOOL 160 
#define  EXPR_BRACKETS 159 
#define  EXPR_CONCAT 158 
#define  EXPR_DIV 157 
#define  EXPR_DOUBLE 156 
#define  EXPR_EMPTY 155 
#define  EXPR_EQUAL 154 
#define  EXPR_EQV 153 
#define  EXPR_EXP 152 
#define  EXPR_GT 151 
#define  EXPR_GTEQ 150 
#define  EXPR_IDIV 149 
#define  EXPR_IMP 148 
#define  EXPR_IS 147 
#define  EXPR_LT 146 
#define  EXPR_LTEQ 145 
#define  EXPR_ME 144 
#define  EXPR_MEMBER 143 
#define  EXPR_MOD 142 
#define  EXPR_MUL 141 
#define  EXPR_NEG 140 
#define  EXPR_NEQUAL 139 
#define  EXPR_NEW 138 
#define  EXPR_NOARG 137 
#define  EXPR_NOT 136 
#define  EXPR_NOTHING 135 
#define  EXPR_NULL 134 
#define  EXPR_OR 133 
#define  EXPR_STRING 132 
#define  EXPR_SUB 131 
#define  EXPR_ULONG 130 
#define  EXPR_USHORT 129 
#define  EXPR_XOR 128 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  OP_add ; 
 int /*<<< orphan*/  OP_and ; 
 int /*<<< orphan*/  OP_bool ; 
 int /*<<< orphan*/  OP_concat ; 
 int /*<<< orphan*/  OP_div ; 
 int /*<<< orphan*/  OP_double ; 
 int /*<<< orphan*/  OP_empty ; 
 int /*<<< orphan*/  OP_equal ; 
 int /*<<< orphan*/  OP_eqv ; 
 int /*<<< orphan*/  OP_exp ; 
 int /*<<< orphan*/  OP_gt ; 
 int /*<<< orphan*/  OP_gteq ; 
 int /*<<< orphan*/  OP_hres ; 
 int /*<<< orphan*/  OP_idiv ; 
 int /*<<< orphan*/  OP_imp ; 
 int /*<<< orphan*/  OP_is ; 
 int /*<<< orphan*/  OP_long ; 
 int /*<<< orphan*/  OP_lt ; 
 int /*<<< orphan*/  OP_lteq ; 
 int /*<<< orphan*/  OP_me ; 
 int /*<<< orphan*/  OP_mod ; 
 int /*<<< orphan*/  OP_mul ; 
 int /*<<< orphan*/  OP_neg ; 
 int /*<<< orphan*/  OP_nequal ; 
 int /*<<< orphan*/  OP_new ; 
 int /*<<< orphan*/  OP_not ; 
 int /*<<< orphan*/  OP_nothing ; 
 int /*<<< orphan*/  OP_null ; 
 int /*<<< orphan*/  OP_or ; 
 int /*<<< orphan*/  OP_short ; 
 int /*<<< orphan*/  OP_string ; 
 int /*<<< orphan*/  OP_sub ; 
 int /*<<< orphan*/  OP_xor ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_binary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_member_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_unary_expression (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_expression(compile_ctx_t *ctx, expression_t *expr)
{
    switch(expr->type) {
    case EXPR_ADD:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_add);
    case EXPR_AND:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_and);
    case EXPR_BOOL:
        return push_instr_int(ctx, OP_bool, ((bool_expression_t*)expr)->value);
    case EXPR_BRACKETS:
        return compile_expression(ctx, ((unary_expression_t*)expr)->subexpr);
    case EXPR_CONCAT:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_concat);
    case EXPR_DIV:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_div);
    case EXPR_DOUBLE:
        return push_instr_double(ctx, OP_double, ((double_expression_t*)expr)->value);
    case EXPR_EMPTY:
        return push_instr(ctx, OP_empty) ? S_OK : E_OUTOFMEMORY;
    case EXPR_EQUAL:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_equal);
    case EXPR_EQV:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_eqv);
    case EXPR_EXP:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_exp);
    case EXPR_GT:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_gt);
    case EXPR_GTEQ:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_gteq);
    case EXPR_IDIV:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_idiv);
    case EXPR_IS:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_is);
    case EXPR_IMP:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_imp);
    case EXPR_LT:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_lt);
    case EXPR_LTEQ:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_lteq);
    case EXPR_ME:
        return push_instr(ctx, OP_me) ? S_OK : E_OUTOFMEMORY;
    case EXPR_MEMBER:
        return compile_member_expression(ctx, (member_expression_t*)expr, TRUE);
    case EXPR_MOD:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_mod);
    case EXPR_MUL:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_mul);
    case EXPR_NEG:
        return compile_unary_expression(ctx, (unary_expression_t*)expr, OP_neg);
    case EXPR_NEQUAL:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_nequal);
    case EXPR_NEW:
        return push_instr_str(ctx, OP_new, ((string_expression_t*)expr)->value);
    case EXPR_NOARG:
        return push_instr_int(ctx, OP_hres, DISP_E_PARAMNOTFOUND);
    case EXPR_NOT:
        return compile_unary_expression(ctx, (unary_expression_t*)expr, OP_not);
    case EXPR_NOTHING:
        return push_instr(ctx, OP_nothing) ? S_OK : E_OUTOFMEMORY;
    case EXPR_NULL:
        return push_instr(ctx, OP_null) ? S_OK : E_OUTOFMEMORY;
    case EXPR_OR:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_or);
    case EXPR_STRING:
        return push_instr_str(ctx, OP_string, ((string_expression_t*)expr)->value);
    case EXPR_SUB:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_sub);
    case EXPR_USHORT:
        return push_instr_int(ctx, OP_short, ((int_expression_t*)expr)->value);
    case EXPR_ULONG:
        return push_instr_int(ctx, OP_long, ((int_expression_t*)expr)->value);
    case EXPR_XOR:
        return compile_binary_expression(ctx, (binary_expression_t*)expr, OP_xor);
    default:
        FIXME("Unimplemented expression type %d\n", expr->type);
        return E_NOTIMPL;
    }

    return S_OK;
}