#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char tok; int /*<<< orphan*/ * fs; int /*<<< orphan*/  linenumber; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_52 ; 
 int /*<<< orphan*/  LJ_ERR_XSYMBOL ; 
 scalar_t__ LJ_FR2 ; 
 char TK_goto ; 
 char TK_name ; 
 char TK_string ; 
 int /*<<< orphan*/  bcemit_method (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcreg_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err_syntax (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_bracket (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_discharge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_field (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_str (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_toanyreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_tonextreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_match (TYPE_1__*,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_args (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_lookup (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void expr_primary(LexState *ls, ExpDesc *v)
{
  FuncState *fs = ls->fs;
  /* Parse prefix expression. */
  if (ls->tok == '(') {
    BCLine line = ls->linenumber;
    lj_lex_next(ls);
    expr(ls, v);
    lex_match(ls, ')', '(', line);
    expr_discharge(ls->fs, v);
  } else if (ls->tok == TK_name || (!LJ_52 && ls->tok == TK_goto)) {
    var_lookup(ls, v);
  } else {
    err_syntax(ls, LJ_ERR_XSYMBOL);
  }
  for (;;) {  /* Parse multiple expression suffixes. */
    if (ls->tok == '.') {
      expr_field(ls, v);
    } else if (ls->tok == '[') {
      ExpDesc key;
      expr_toanyreg(fs, v);
      expr_bracket(ls, &key);
      expr_index(fs, v, &key);
    } else if (ls->tok == ':') {
      ExpDesc key;
      lj_lex_next(ls);
      expr_str(ls, &key);
      bcemit_method(fs, v, &key);
      parse_args(ls, v);
    } else if (ls->tok == '(' || ls->tok == TK_string || ls->tok == '{') {
      expr_tonextreg(fs, v);
      if (LJ_FR2) bcreg_reserve(fs, 1);
      parse_args(ls, v);
    } else {
      break;
    }
  }
}