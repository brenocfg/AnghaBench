#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_16__ {int tt; } ;
struct TYPE_17__ {TYPE_2__ gch; } ;
struct TYPE_15__ {int /*<<< orphan*/  nuse; } ;
struct TYPE_14__ {TYPE_1__ strt; int /*<<< orphan*/ * mainthread; } ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
 TYPE_13__* G (int /*<<< orphan*/ *) ; 
#define  LUA_TFUNCTION 134 
#define  LUA_TPROTO 133 
#define  LUA_TSTRING 132 
#define  LUA_TTABLE 131 
#define  LUA_TTHREAD 130 
#define  LUA_TUPVAL 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  gco2cl (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2h (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2p (TYPE_3__*) ; 
 int /*<<< orphan*/ * gco2th (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2ts (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2u (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2uv (TYPE_3__*) ; 
 int /*<<< orphan*/  luaE_freethread (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaF_freeclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeupval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_freemem (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  sizestring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeudata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeobj (lua_State *L, GCObject *o) {
  switch (o->gch.tt) {
    case LUA_TPROTO: luaF_freeproto(L, gco2p(o)); break;
    case LUA_TFUNCTION: luaF_freeclosure(L, gco2cl(o)); break;
    case LUA_TUPVAL: luaF_freeupval(L, gco2uv(o)); break;
    case LUA_TTABLE: luaH_free(L, gco2h(o)); break;
    case LUA_TTHREAD: {
      lua_assert(gco2th(o) != L && gco2th(o) != G(L)->mainthread);
      luaE_freethread(L, gco2th(o));
      break;
    }
    case LUA_TSTRING: {
      G(L)->strt.nuse--;
      luaM_freemem(L, o, sizestring(gco2ts(o)));
      break;
    }
    case LUA_TUSERDATA: {
      luaM_freemem(L, o, sizeudata(gco2u(o)));
      break;
    }
    default: lua_assert(0);
  }
}