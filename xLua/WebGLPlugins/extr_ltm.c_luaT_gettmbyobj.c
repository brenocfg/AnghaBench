#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_6__ {int /*<<< orphan*/ * tmname; int /*<<< orphan*/ ** mt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * metatable; } ;
struct TYPE_4__ {int /*<<< orphan*/ * metatable; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  size_t TMS ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
#define  LUA_TTABLE 129 
#define  LUA_TUSERDATA 128 
 TYPE_2__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* luaH_getshortstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 size_t ttnov (int /*<<< orphan*/  const*) ; 
 TYPE_1__* uvalue (int /*<<< orphan*/  const*) ; 

const TValue *luaT_gettmbyobj (lua_State *L, const TValue *o, TMS event) {
  Table *mt;
  switch (ttnov(o)) {
    case LUA_TTABLE:
      mt = hvalue(o)->metatable;
      break;
    case LUA_TUSERDATA:
      mt = uvalue(o)->metatable;
      break;
    default:
      mt = G(L)->mt[ttnov(o)];
  }
  return (mt ? luaH_getshortstr(mt, G(L)->tmname[event]) : luaO_nilobject);
}