#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_8__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  tok; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  size_t BinOpr ;

/* Variables and functions */
 size_t OPR_NOBINOPR ; 
 int /*<<< orphan*/  bcemit_binop (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcemit_binop_left (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_unop (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 TYPE_4__* priority ; 
 int /*<<< orphan*/  synlevel_begin (TYPE_1__*) ; 
 int /*<<< orphan*/  synlevel_end (TYPE_1__*) ; 
 size_t token2binop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BinOpr expr_binop(LexState *ls, ExpDesc *v, uint32_t limit)
{
  BinOpr op;
  synlevel_begin(ls);
  expr_unop(ls, v);
  op = token2binop(ls->tok);
  while (op != OPR_NOBINOPR && priority[op].left > limit) {
    ExpDesc v2;
    BinOpr nextop;
    lj_lex_next(ls);
    bcemit_binop_left(ls->fs, op, v);
    /* Parse binary expression with higher priority. */
    nextop = expr_binop(ls, &v2, priority[op].right);
    bcemit_binop(ls->fs, op, v, &v2);
    op = nextop;
  }
  synlevel_end(ls);
  return op;  /* Return unconsumed binary operator (if any). */
}