#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char tok; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  FSCOPE_LOOP ; 
 int /*<<< orphan*/  LJ_ERR_XFOR ; 
 int /*<<< orphan*/  TK_end ; 
 int /*<<< orphan*/  TK_for ; 
 char TK_in ; 
 int /*<<< orphan*/  err_syntax (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lex_str (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_for_iter (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_for_num (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_for(LexState *ls, BCLine line)
{
  FuncState *fs = ls->fs;
  GCstr *varname;
  FuncScope bl;
  fscope_begin(fs, &bl, FSCOPE_LOOP);
  lj_lex_next(ls);  /* Skip 'for'. */
  varname = lex_str(ls);  /* Get first variable name. */
  if (ls->tok == '=')
    parse_for_num(ls, varname, line);
  else if (ls->tok == ',' || ls->tok == TK_in)
    parse_for_iter(ls, varname);
  else
    err_syntax(ls, LJ_ERR_XFOR);
  lex_match(ls, TK_end, TK_for, line);
  fscope_end(fs);  /* Resolve break list. */
}