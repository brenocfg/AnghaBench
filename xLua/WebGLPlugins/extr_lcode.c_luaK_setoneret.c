#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  info; } ;
struct TYPE_6__ {scalar_t__ k; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_A (int /*<<< orphan*/ ) ; 
 int GETARG_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VCALL ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VRELOCABLE ; 
 scalar_t__ VVARARG ; 
 int /*<<< orphan*/  getinstruction (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void luaK_setoneret (FuncState *fs, expdesc *e) {
  if (e->k == VCALL) {  /* expression is an open function call? */
    /* already returns 1 value */
    lua_assert(GETARG_C(getinstruction(fs, e)) == 2);
    e->k = VNONRELOC;  /* result has fixed position */
    e->u.info = GETARG_A(getinstruction(fs, e));
  }
  else if (e->k == VVARARG) {
    SETARG_B(getinstruction(fs, e), 2);
    e->k = VRELOCABLE;  /* can relocate its simple result */
  }
}