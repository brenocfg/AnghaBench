#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  str_len; int /*<<< orphan*/  str; } ;
struct TYPE_11__ {TYPE_3__ regexp; int /*<<< orphan*/  wstr; int /*<<< orphan*/  dval; int /*<<< orphan*/  bval; } ;
struct TYPE_12__ {int type; TYPE_4__ u; } ;
typedef  TYPE_5__ literal_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_9__ {TYPE_1__* arg; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  uint; int /*<<< orphan*/ * str; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
#define  LT_BOOL 132 
#define  LT_DOUBLE 131 
#define  LT_NULL 130 
#define  LT_REGEXP 129 
#define  LT_STRING 128 
 int /*<<< orphan*/  OP_bool ; 
 int /*<<< orphan*/  OP_double ; 
 int /*<<< orphan*/  OP_null ; 
 int /*<<< orphan*/  OP_regexp ; 
 int /*<<< orphan*/  OP_str ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * compiler_alloc_string_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* instr_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_literal(compiler_ctx_t *ctx, literal_t *literal)
{
    switch(literal->type) {
    case LT_BOOL:
        return push_instr_int(ctx, OP_bool, literal->u.bval);
    case LT_DOUBLE:
        return push_instr_double(ctx, OP_double, literal->u.dval);
    case LT_NULL:
        return push_instr(ctx, OP_null) ? S_OK : E_OUTOFMEMORY;
    case LT_STRING:
        return push_instr_str(ctx, OP_str, literal->u.wstr);
    case LT_REGEXP: {
        unsigned instr;
        jsstr_t *str;

        str = compiler_alloc_string_len(ctx, literal->u.regexp.str, literal->u.regexp.str_len);
        if(!str)
            return E_OUTOFMEMORY;

        instr = push_instr(ctx, OP_regexp);
        if(!instr)
            return E_OUTOFMEMORY;

        instr_ptr(ctx, instr)->u.arg[0].str = str;
        instr_ptr(ctx, instr)->u.arg[1].uint = literal->u.regexp.flags;
        return S_OK;
    }
    DEFAULT_UNREACHABLE;
    }
    return E_FAIL;
}