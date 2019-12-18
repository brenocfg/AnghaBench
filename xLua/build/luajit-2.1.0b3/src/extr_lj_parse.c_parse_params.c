#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ nactvar; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {char tok; TYPE_2__* fs; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_52 ; 
 int /*<<< orphan*/  LJ_ERR_XPARAM ; 
 int /*<<< orphan*/  PROTO_VARARG ; 
 char TK_dots ; 
 char TK_goto ; 
 char TK_name ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  err_syntax (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_check (TYPE_1__*,char) ; 
 scalar_t__ lex_opt (TYPE_1__*,char) ; 
 int /*<<< orphan*/  lex_str (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  var_add (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  var_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_new_lit (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static BCReg parse_params(LexState *ls, int needself)
{
  FuncState *fs = ls->fs;
  BCReg nparams = 0;
  lex_check(ls, '(');
  if (needself)
    var_new_lit(ls, nparams++, "self");
  if (ls->tok != ')') {
    do {
      if (ls->tok == TK_name || (!LJ_52 && ls->tok == TK_goto)) {
	var_new(ls, nparams++, lex_str(ls));
      } else if (ls->tok == TK_dots) {
	lj_lex_next(ls);
	fs->flags |= PROTO_VARARG;
	break;
      } else {
	err_syntax(ls, LJ_ERR_XPARAM);
      }
    } while (lex_opt(ls, ','));
  }
  var_add(ls, nparams);
  lua_assert(fs->nactvar == nparams);
  bcreg_reserve(fs, nparams);
  lex_check(ls, ')');
  return nparams;
}