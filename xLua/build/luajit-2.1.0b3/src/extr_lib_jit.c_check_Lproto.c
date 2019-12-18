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
typedef  int /*<<< orphan*/  GCproto ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  funcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * funcproto (int /*<<< orphan*/ ) ; 
 scalar_t__ isluafunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * protoV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisproto (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GCproto *check_Lproto(lua_State *L, int nolua)
{
  TValue *o = L->base;
  if (L->top > o) {
    if (tvisproto(o)) {
      return protoV(o);
    } else if (tvisfunc(o)) {
      if (isluafunc(funcV(o)))
	return funcproto(funcV(o));
      else if (nolua)
	return NULL;
    }
  }
  lj_err_argt(L, 1, LUA_TFUNCTION);
  return NULL;  /* unreachable */
}