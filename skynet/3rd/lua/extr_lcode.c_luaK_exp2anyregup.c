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
struct TYPE_5__ {scalar_t__ k; } ;
typedef  TYPE_1__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ VUPVAL ; 
 scalar_t__ hasjumps (TYPE_1__*) ; 
 int /*<<< orphan*/  luaK_exp2anyreg (int /*<<< orphan*/ *,TYPE_1__*) ; 

void luaK_exp2anyregup (FuncState *fs, expdesc *e) {
  if (e->k != VUPVAL || hasjumps(e))
    luaK_exp2anyreg(fs, e);
}