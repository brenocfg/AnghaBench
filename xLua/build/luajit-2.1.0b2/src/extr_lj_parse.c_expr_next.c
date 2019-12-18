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
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  ExpDesc ;

/* Variables and functions */
 int /*<<< orphan*/  expr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_tonextreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void expr_next(LexState *ls)
{
  ExpDesc e;
  expr(ls, &e);
  expr_tonextreg(ls->fs, &e);
}