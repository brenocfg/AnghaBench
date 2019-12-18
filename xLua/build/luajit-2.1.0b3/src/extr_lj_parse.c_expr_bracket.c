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
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  ExpDesc ;

/* Variables and functions */
 int /*<<< orphan*/  expr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_toval (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_check (TYPE_1__*,char) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 

__attribute__((used)) static void expr_bracket(LexState *ls, ExpDesc *v)
{
  lj_lex_next(ls);  /* Skip '['. */
  expr(ls, v);
  expr_toval(ls->fs, v);
  lex_check(ls, ']');
}