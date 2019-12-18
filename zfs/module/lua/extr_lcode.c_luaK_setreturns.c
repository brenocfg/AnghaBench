#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ k; } ;
typedef  TYPE_1__ expdesc ;
struct TYPE_9__ {int /*<<< orphan*/  freereg; } ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  SETARG_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETARG_C (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VCALL ; 
 scalar_t__ VVARARG ; 
 int /*<<< orphan*/  getcode (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_2__*,int) ; 

void luaK_setreturns (FuncState *fs, expdesc *e, int nresults) {
  if (e->k == VCALL) {  /* expression is an open function call? */
    SETARG_C(getcode(fs, e), nresults+1);
  }
  else if (e->k == VVARARG) {
    SETARG_B(getcode(fs, e), nresults+1);
    SETARG_A(getcode(fs, e), fs->freereg);
    luaK_reserveregs(fs, 1);
  }
}