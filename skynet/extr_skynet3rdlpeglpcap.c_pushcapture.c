#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_20__ {TYPE_15__* cap; int /*<<< orphan*/  ptop; scalar_t__ s; int /*<<< orphan*/ * L; } ;
struct TYPE_19__ {int /*<<< orphan*/  idx; } ;
struct TYPE_18__ {int idx; } ;
struct TYPE_17__ {int /*<<< orphan*/  idx; scalar_t__ s; } ;
typedef  TYPE_3__ CapState ;

/* Variables and functions */
#define  Carg 141 
#define  Cbackref 140 
#define  Cconst 139 
#define  Cfold 138 
#define  Cfunction 137 
#define  Cgroup 136 
#define  Cnum 135 
#define  Cposition 134 
#define  Cquery 133 
#define  Cruntime 132 
#define  Csimple 131 
#define  Cstring 130 
#define  Csubst 129 
#define  Ctable 128 
 int /*<<< orphan*/  FIXEDARGS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int backrefcap (TYPE_3__*) ; 
 int captype (TYPE_15__*) ; 
 int foldcap (TYPE_3__*) ; 
 int functioncap (TYPE_3__*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nextcap (TYPE_3__*) ; 
 int numcap (TYPE_3__*) ; 
 int /*<<< orphan*/  pushluaval (TYPE_3__*) ; 
 int pushnestedvalues (TYPE_3__*,int) ; 
 int querycap (TYPE_3__*) ; 
 int /*<<< orphan*/  stringcap (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  substcap (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int tablecap (TYPE_3__*) ; 

__attribute__((used)) static int pushcapture (CapState *cs) {
  lua_State *L = cs->L;
  luaL_checkstack(L, 4, "too many captures");
  switch (captype(cs->cap)) {
    case Cposition: {
      lua_pushinteger(L, cs->cap->s - cs->s + 1);
      cs->cap++;
      return 1;
    }
    case Cconst: {
      pushluaval(cs);
      cs->cap++;
      return 1;
    }
    case Carg: {
      int arg = (cs->cap++)->idx;
      if (arg + FIXEDARGS > cs->ptop)
        return luaL_error(L, "reference to absent extra argument #%d", arg);
      lua_pushvalue(L, arg + FIXEDARGS);
      return 1;
    }
    case Csimple: {
      int k = pushnestedvalues(cs, 1);
      lua_insert(L, -k);  /* make whole match be first result */
      return k;
    }
    case Cruntime: {
      lua_pushvalue(L, (cs->cap++)->idx);  /* value is in the stack */
      return 1;
    }
    case Cstring: {
      luaL_Buffer b;
      luaL_buffinit(L, &b);
      stringcap(&b, cs);
      luaL_pushresult(&b);
      return 1;
    }
    case Csubst: {
      luaL_Buffer b;
      luaL_buffinit(L, &b);
      substcap(&b, cs);
      luaL_pushresult(&b);
      return 1;
    }
    case Cgroup: {
      if (cs->cap->idx == 0)  /* anonymous group? */
        return pushnestedvalues(cs, 0);  /* add all nested values */
      else {  /* named group: add no values */
        nextcap(cs);  /* skip capture */
        return 0;
      }
    }
    case Cbackref: return backrefcap(cs);
    case Ctable: return tablecap(cs);
    case Cfunction: return functioncap(cs);
    case Cnum: return numcap(cs);
    case Cquery: return querycap(cs);
    case Cfold: return foldcap(cs);
    default: assert(0); return 0;
  }
}