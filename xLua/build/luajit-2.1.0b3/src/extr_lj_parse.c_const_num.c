#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {int /*<<< orphan*/  nval; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  nkn; int /*<<< orphan*/  kt; int /*<<< orphan*/ * L; } ;
struct TYPE_12__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ TValue ;
typedef  TYPE_3__ FuncState ;
typedef  TYPE_4__ ExpDesc ;
typedef  int /*<<< orphan*/  BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  expr_isnumk (TYPE_4__*) ; 
 TYPE_2__* lj_tab_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ tvhaskslot (TYPE_2__*) ; 
 int /*<<< orphan*/  tvkslot (TYPE_2__*) ; 

__attribute__((used)) static BCReg const_num(FuncState *fs, ExpDesc *e)
{
  lua_State *L = fs->L;
  TValue *o;
  lua_assert(expr_isnumk(e));
  o = lj_tab_set(L, fs->kt, &e->u.nval);
  if (tvhaskslot(o))
    return tvkslot(o);
  o->u64 = fs->nkn;
  return fs->nkn++;
}