#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LexState ;
typedef  int /*<<< orphan*/  BCPos ;

/* Variables and functions */
 int /*<<< orphan*/  TK_then ; 
 int /*<<< orphan*/  expr_cond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_block (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BCPos parse_then(LexState *ls)
{
  BCPos condexit;
  lj_lex_next(ls);  /* Skip 'if' or 'elseif'. */
  condexit = expr_cond(ls);
  lex_check(ls, TK_then);
  parse_block(ls);
  return condexit;
}