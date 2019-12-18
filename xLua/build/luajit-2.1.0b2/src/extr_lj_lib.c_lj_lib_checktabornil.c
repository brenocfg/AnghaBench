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
struct TYPE_4__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_NOTABN ; 
 int /*<<< orphan*/  lj_err_arg (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tabV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 

GCtab *lj_lib_checktabornil(lua_State *L, int narg)
{
  TValue *o = L->base + narg-1;
  if (o < L->top) {
    if (tvistab(o))
      return tabV(o);
    else if (tvisnil(o))
      return NULL;
  }
  lj_err_arg(L, narg, LJ_ERR_NOTABN);
  return NULL;  /* unreachable */
}