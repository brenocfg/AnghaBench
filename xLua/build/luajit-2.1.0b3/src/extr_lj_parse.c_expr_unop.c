#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char tok; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  int /*<<< orphan*/  BCOp ;

/* Variables and functions */
 int /*<<< orphan*/  BC_LEN ; 
 int /*<<< orphan*/  BC_NOT ; 
 int /*<<< orphan*/  BC_UNM ; 
 char TK_not ; 
 int /*<<< orphan*/  UNARY_PRIORITY ; 
 int /*<<< orphan*/  bcemit_unop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_binop (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_simple (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 

__attribute__((used)) static void expr_unop(LexState *ls, ExpDesc *v)
{
  BCOp op;
  if (ls->tok == TK_not) {
    op = BC_NOT;
  } else if (ls->tok == '-') {
    op = BC_UNM;
  } else if (ls->tok == '#') {
    op = BC_LEN;
  } else {
    expr_simple(ls, v);
    return;
  }
  lj_lex_next(ls);
  expr_binop(ls, v, UNARY_PRIORITY);
  bcemit_unop(ls->fs, op, v);
}