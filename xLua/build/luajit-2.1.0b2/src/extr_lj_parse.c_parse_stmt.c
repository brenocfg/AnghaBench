#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int tok; int /*<<< orphan*/  linenumber; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_52 ; 
#define  TK_break 138 
#define  TK_do 137 
 int /*<<< orphan*/  TK_end ; 
#define  TK_for 136 
#define  TK_function 135 
#define  TK_goto 134 
#define  TK_if 133 
#define  TK_label 132 
#define  TK_local 131 
 int /*<<< orphan*/  TK_name ; 
#define  TK_repeat 130 
#define  TK_return 129 
#define  TK_while 128 
 int /*<<< orphan*/  lex_match (TYPE_1__*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_lookahead (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_block (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_break (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_call_assign (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_for (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_func (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_goto (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_if (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_label (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_local (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_repeat (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_return (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_while (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_stmt(LexState *ls)
{
  BCLine line = ls->linenumber;
  switch (ls->tok) {
  case TK_if:
    parse_if(ls, line);
    break;
  case TK_while:
    parse_while(ls, line);
    break;
  case TK_do:
    lj_lex_next(ls);
    parse_block(ls);
    lex_match(ls, TK_end, TK_do, line);
    break;
  case TK_for:
    parse_for(ls, line);
    break;
  case TK_repeat:
    parse_repeat(ls, line);
    break;
  case TK_function:
    parse_func(ls, line);
    break;
  case TK_local:
    lj_lex_next(ls);
    parse_local(ls);
    break;
  case TK_return:
    parse_return(ls);
    return 1;  /* Must be last. */
  case TK_break:
    lj_lex_next(ls);
    parse_break(ls);
    return !LJ_52;  /* Must be last in Lua 5.1. */
#if LJ_52
  case ';':
    lj_lex_next(ls);
    break;
#endif
  case TK_label:
    parse_label(ls);
    break;
  case TK_goto:
    if (LJ_52 || lj_lex_lookahead(ls) == TK_name) {
      lj_lex_next(ls);
      parse_goto(ls);
      break;
    }  /* else: fallthrough */
  default:
    parse_call_assign(ls);
    break;
  }
  return 0;
}