#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 scalar_t__ LJ_LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TSTRING ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_strfmt_number (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setstrV (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisstr (int /*<<< orphan*/ *) ; 

GCstr *lj_lib_checkstr(lua_State *L, int narg)
{
  TValue *o = L->base + narg-1;
  if (o < L->top) {
    if (LJ_LIKELY(tvisstr(o))) {
      return strV(o);
    } else if (tvisnumber(o)) {
      GCstr *s = lj_strfmt_number(L, o);
      setstrV(L, o, s);
      return s;
    }
  }
  lj_err_argt(L, narg, LUA_TSTRING);
  return NULL;  /* unreachable */
}