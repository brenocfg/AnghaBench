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
struct TYPE_5__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  ExpDesc ;

/* Variables and functions */
 int /*<<< orphan*/  expr_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_str (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_toanyreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 

__attribute__((used)) static void expr_field(LexState *ls, ExpDesc *v)
{
  FuncState *fs = ls->fs;
  ExpDesc key;
  expr_toanyreg(fs, v);
  lj_lex_next(ls);  /* Skip dot or colon. */
  expr_str(ls, &key);
  expr_index(fs, v, &key);
}