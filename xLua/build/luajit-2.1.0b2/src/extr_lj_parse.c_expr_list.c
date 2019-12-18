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
struct TYPE_5__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  int BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  expr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_tonextreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ lex_opt (TYPE_1__*,char) ; 

__attribute__((used)) static BCReg expr_list(LexState *ls, ExpDesc *v)
{
  BCReg n = 1;
  expr(ls, v);
  while (lex_opt(ls, ',')) {
    expr_tonextreg(ls->fs, v);
    expr(ls, v);
    n++;
  }
  return n;
}