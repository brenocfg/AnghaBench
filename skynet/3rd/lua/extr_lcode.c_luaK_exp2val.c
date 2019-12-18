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
typedef  int /*<<< orphan*/  expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ hasjumps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_dischargevars (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_exp2anyreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void luaK_exp2val (FuncState *fs, expdesc *e) {
  if (hasjumps(e))
    luaK_exp2anyreg(fs, e);
  else
    luaK_dischargevars(fs, e);
}