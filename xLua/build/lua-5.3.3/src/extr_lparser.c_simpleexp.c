#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  ival; int /*<<< orphan*/  nval; } ;
struct TYPE_26__ {TYPE_1__ u; } ;
typedef  TYPE_5__ expdesc ;
struct TYPE_28__ {TYPE_4__* f; } ;
struct TYPE_23__ {int /*<<< orphan*/  ts; int /*<<< orphan*/  i; int /*<<< orphan*/  r; } ;
struct TYPE_24__ {int token; TYPE_2__ seminfo; } ;
struct TYPE_27__ {int /*<<< orphan*/  linenumber; TYPE_7__* fs; TYPE_3__ t; } ;
struct TYPE_25__ {int is_vararg; } ;
typedef  TYPE_6__ LexState ;
typedef  TYPE_7__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_VARARG ; 
#define  TK_DOTS 135 
#define  TK_FALSE 134 
#define  TK_FLT 133 
#define  TK_FUNCTION 132 
#define  TK_INT 131 
#define  TK_NIL 130 
#define  TK_STRING 129 
#define  TK_TRUE 128 
 int /*<<< orphan*/  VFALSE ; 
 int /*<<< orphan*/  VKFLT ; 
 int /*<<< orphan*/  VKINT ; 
 int /*<<< orphan*/  VNIL ; 
 int /*<<< orphan*/  VTRUE ; 
 int /*<<< orphan*/  VVARARG ; 
 int /*<<< orphan*/  body (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_condition (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  codestring (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constructor (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  init_exp (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_next (TYPE_6__*) ; 
 int /*<<< orphan*/  suffixedexp (TYPE_6__*,TYPE_5__*) ; 

__attribute__((used)) static void simpleexp (LexState *ls, expdesc *v) {
  /* simpleexp -> FLT | INT | STRING | NIL | TRUE | FALSE | ... |
                  constructor | FUNCTION body | suffixedexp */
  switch (ls->t.token) {
    case TK_FLT: {
      init_exp(v, VKFLT, 0);
      v->u.nval = ls->t.seminfo.r;
      break;
    }
    case TK_INT: {
      init_exp(v, VKINT, 0);
      v->u.ival = ls->t.seminfo.i;
      break;
    }
    case TK_STRING: {
      codestring(ls, v, ls->t.seminfo.ts);
      break;
    }
    case TK_NIL: {
      init_exp(v, VNIL, 0);
      break;
    }
    case TK_TRUE: {
      init_exp(v, VTRUE, 0);
      break;
    }
    case TK_FALSE: {
      init_exp(v, VFALSE, 0);
      break;
    }
    case TK_DOTS: {  /* vararg */
      FuncState *fs = ls->fs;
      check_condition(ls, fs->f->is_vararg,
                      "cannot use '...' outside a vararg function");
      fs->f->is_vararg = 1;  /* function actually uses vararg */
      init_exp(v, VVARARG, luaK_codeABC(fs, OP_VARARG, 0, 1, 0));
      break;
    }
    case '{': {  /* constructor */
      constructor(ls, v);
      return;
    }
    case TK_FUNCTION: {
      luaX_next(ls);
      body(ls, v, 0, ls->linenumber);
      return;
    }
    default: {
      suffixedexp(ls, v);
      return;
    }
  }
  luaX_next(ls);
}