#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_7__ {scalar_t__ freereg; } ;
typedef  TYPE_1__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  exp2reg (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  freeexp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_dischargevars (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_1__*,int) ; 

void luaK_exp2nextreg (FuncState *fs, expdesc *e) {
  luaK_dischargevars(fs, e);
  freeexp(fs, e);
  luaK_reserveregs(fs, 1);
  exp2reg(fs, e, fs->freereg - 1);
}