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
struct TYPE_5__ {scalar_t__ tok; int /*<<< orphan*/  tokval; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 scalar_t__ LJ_52 ; 
 scalar_t__ TK_goto ; 
 scalar_t__ TK_name ; 
 int /*<<< orphan*/  err_token (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GCstr *lex_str(LexState *ls)
{
  GCstr *s;
  if (ls->tok != TK_name && (LJ_52 || ls->tok != TK_goto))
    err_token(ls, TK_name);
  s = strV(&ls->tokval);
  lj_lex_next(ls);
  return s;
}