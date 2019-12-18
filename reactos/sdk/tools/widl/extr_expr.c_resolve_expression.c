#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void type_t ;
struct expression_type {void* type; void* is_variable; void* is_temporary; } ;
struct expr_loc {char* attr; TYPE_2__* v; } ;
struct TYPE_5__ {void* tref; TYPE_3__* ext; int /*<<< orphan*/  sval; } ;
struct TYPE_7__ {int type; TYPE_1__ u; struct TYPE_7__* ref; struct TYPE_7__* ext2; } ;
typedef  TYPE_3__ expr_t ;
struct TYPE_6__ {int /*<<< orphan*/  loc_info; } ;

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
 void* FALSE ; 
 int /*<<< orphan*/  FC_UP ; 
 void* TRUE ; 
 int /*<<< orphan*/  TYPE_BASIC_CHAR ; 
 int /*<<< orphan*/  TYPE_BASIC_DOUBLE ; 
 int /*<<< orphan*/  TYPE_BASIC_INT ; 
 int /*<<< orphan*/  TYPE_BASIC_WCHAR ; 
 int /*<<< orphan*/  check_arithmetic_type (struct expr_loc const*,void const*,void*) ; 
 int /*<<< orphan*/  check_integer_type (struct expr_loc const*,void const*,void*) ; 
 int /*<<< orphan*/  check_scalar_type (struct expr_loc const*,void const*,void*) ; 
 int /*<<< orphan*/  error_loc_info (int /*<<< orphan*/ *,char*,...) ; 
 void* find_identifier (int /*<<< orphan*/ ,void const*,int*) ; 
 int /*<<< orphan*/  is_array (void*) ; 
 int /*<<< orphan*/  is_integer_type (void*) ; 
 int /*<<< orphan*/  is_ptr (void*) ; 
 int /*<<< orphan*/  is_valid_member_operand (void*) ; 
 void* type_array_get_element (void*) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (void*) ; 
 void* type_new_basic (int /*<<< orphan*/ ) ; 
 void* type_new_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* type_new_pointer (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 void* type_pointer_get_ref (void*) ; 

__attribute__((used)) static struct expression_type resolve_expression(const struct expr_loc *expr_loc,
                                                 const type_t *cont_type,
                                                 const expr_t *e)
{
    struct expression_type result;
    result.is_variable = FALSE;
    result.is_temporary = FALSE;
    result.type = NULL;
    switch (e->type)
    {
    case EXPR_VOID:
        break;
    case EXPR_HEXNUM:
    case EXPR_NUM:
    case EXPR_TRUEFALSE:
        result.is_temporary = FALSE;
        result.type = type_new_int(TYPE_BASIC_INT, 0);
        break;
    case EXPR_STRLIT:
        result.is_temporary = TRUE;
        result.type = type_new_pointer(FC_UP, type_new_int(TYPE_BASIC_CHAR, 0), NULL);
        break;
    case EXPR_WSTRLIT:
        result.is_temporary = TRUE;
        result.type = type_new_pointer(FC_UP, type_new_int(TYPE_BASIC_WCHAR, 0), NULL);
        break;
    case EXPR_CHARCONST:
        result.is_temporary = TRUE;
        result.type = type_new_int(TYPE_BASIC_CHAR, 0);
        break;
    case EXPR_DOUBLE:
        result.is_temporary = TRUE;
        result.type = type_new_basic(TYPE_BASIC_DOUBLE);
        break;
    case EXPR_IDENTIFIER:
    {
        int found_in_cont_type;
        result.is_variable = TRUE;
        result.is_temporary = FALSE;
        result.type = find_identifier(e->u.sval, cont_type, &found_in_cont_type);
        if (!result.type)
        {
            error_loc_info(&expr_loc->v->loc_info, "identifier %s cannot be resolved in expression%s%s\n",
                           e->u.sval, expr_loc->attr ? " for attribute " : "",
                           expr_loc->attr ? expr_loc->attr : "");
        }
        break;
    }
    case EXPR_LOGNOT:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        check_scalar_type(expr_loc, cont_type, result.type);
        result.is_variable = FALSE;
        result.is_temporary = FALSE;
        result.type = type_new_int(TYPE_BASIC_INT, 0);
        break;
    case EXPR_NOT:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        check_integer_type(expr_loc, cont_type, result.type);
        result.is_variable = FALSE;
        break;
    case EXPR_POS:
    case EXPR_NEG:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        check_arithmetic_type(expr_loc, cont_type, result.type);
        result.is_variable = FALSE;
        break;
    case EXPR_ADDRESSOF:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        if (!result.is_variable)
            error_loc_info(&expr_loc->v->loc_info, "address-of operator applied to non-variable type in expression%s%s\n",
                           expr_loc->attr ? " for attribute " : "",
                           expr_loc->attr ? expr_loc->attr : "");
        result.is_variable = FALSE;
        result.is_temporary = TRUE;
        result.type = type_new_pointer(FC_UP, result.type, NULL);
        break;
    case EXPR_PPTR:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        if (result.type && is_ptr(result.type))
            result.type = type_pointer_get_ref(result.type);
        else if(result.type && is_array(result.type)
                            && type_array_is_decl_as_ptr(result.type))
            result.type = type_array_get_element(result.type);
        else
            error_loc_info(&expr_loc->v->loc_info, "dereference operator applied to non-pointer type in expression%s%s\n",
                           expr_loc->attr ? " for attribute " : "",
                           expr_loc->attr ? expr_loc->attr : "");
        break;
    case EXPR_CAST:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        result.type = e->u.tref;
        break;
    case EXPR_SIZEOF:
        result.is_temporary = FALSE;
        result.type = type_new_int(TYPE_BASIC_INT, 0);
        break;
    case EXPR_SHL:
    case EXPR_SHR:
    case EXPR_MOD:
    case EXPR_MUL:
    case EXPR_DIV:
    case EXPR_ADD:
    case EXPR_SUB:
    case EXPR_AND:
    case EXPR_OR:
    case EXPR_XOR:
    {
        struct expression_type result_right;
        result = resolve_expression(expr_loc, cont_type, e->ref);
        result.is_variable = FALSE;
        result_right = resolve_expression(expr_loc, cont_type, e->u.ext);
        /* FIXME: these checks aren't strict enough for some of the operators */
        check_scalar_type(expr_loc, cont_type, result.type);
        check_scalar_type(expr_loc, cont_type, result_right.type);
        break;
    }
    case EXPR_LOGOR:
    case EXPR_LOGAND:
    case EXPR_EQUALITY:
    case EXPR_INEQUALITY:
    case EXPR_GTR:
    case EXPR_LESS:
    case EXPR_GTREQL:
    case EXPR_LESSEQL:
    {
        struct expression_type result_left, result_right;
        result_left = resolve_expression(expr_loc, cont_type, e->ref);
        result_right = resolve_expression(expr_loc, cont_type, e->u.ext);
        check_scalar_type(expr_loc, cont_type, result_left.type);
        check_scalar_type(expr_loc, cont_type, result_right.type);
        result.is_temporary = FALSE;
        result.type = type_new_int(TYPE_BASIC_INT, 0);
        break;
    }
    case EXPR_MEMBER:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        if (result.type && is_valid_member_operand(result.type))
            result = resolve_expression(expr_loc, result.type, e->u.ext);
        else
            error_loc_info(&expr_loc->v->loc_info, "'.' or '->' operator applied to a type that isn't a structure, union or enumeration in expression%s%s\n",
                           expr_loc->attr ? " for attribute " : "",
                           expr_loc->attr ? expr_loc->attr : "");
        break;
    case EXPR_COND:
    {
        struct expression_type result_first, result_second, result_third;
        result_first = resolve_expression(expr_loc, cont_type, e->ref);
        check_scalar_type(expr_loc, cont_type, result_first.type);
        result_second = resolve_expression(expr_loc, cont_type, e->u.ext);
        result_third = resolve_expression(expr_loc, cont_type, e->ext2);
        check_scalar_type(expr_loc, cont_type, result_second.type);
        check_scalar_type(expr_loc, cont_type, result_third.type);
        if (!is_ptr(result_second.type) ^ !is_ptr(result_third.type))
            error_loc_info(&expr_loc->v->loc_info, "type mismatch in ?: expression\n" );
        /* FIXME: determine the correct return type */
        result = result_second;
        result.is_variable = FALSE;
        break;
    }
    case EXPR_ARRAY:
        result = resolve_expression(expr_loc, cont_type, e->ref);
        if (result.type && is_array(result.type))
        {
            struct expression_type index_result;
            result.type = type_array_get_element(result.type);
            index_result = resolve_expression(expr_loc, cont_type /* FIXME */, e->u.ext);
            if (!index_result.type || !is_integer_type(index_result.type))
                error_loc_info(&expr_loc->v->loc_info, "array subscript not of integral type in expression%s%s\n",
                               expr_loc->attr ? " for attribute " : "",
                               expr_loc->attr ? expr_loc->attr : "");
        }
        else
            error_loc_info(&expr_loc->v->loc_info, "array subscript operator applied to non-array type in expression%s%s\n",
                           expr_loc->attr ? " for attribute " : "",
                           expr_loc->attr ? expr_loc->attr : "");
        break;
    }
    return result;
}