#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lookahead; int /*<<< orphan*/  lookaheadval; } ;
typedef  scalar_t__ LexToken ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 scalar_t__ TK_eof ; 
 scalar_t__ lex_scan (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

LexToken lj_lex_lookahead(LexState *ls)
{
  lua_assert(ls->lookahead == TK_eof);
  ls->lookahead = lex_scan(ls, &ls->lookaheadval);
  return ls->lookahead;
}