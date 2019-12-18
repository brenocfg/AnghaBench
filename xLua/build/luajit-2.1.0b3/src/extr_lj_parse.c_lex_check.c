#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tok; } ;
typedef  int /*<<< orphan*/  LexToken ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  err_token (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 

__attribute__((used)) static void lex_check(LexState *ls, LexToken tok)
{
  if (ls->tok != tok)
    err_token(ls, tok);
  lj_lex_next(ls);
}