#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_26__ ;
typedef  struct TYPE_32__   TYPE_24__ ;
typedef  struct TYPE_31__   TYPE_22__ ;
typedef  struct TYPE_30__   TYPE_20__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;

/* Type definitions */
struct TYPE_36__ {TYPE_6__* gray; } ;
typedef  TYPE_4__ global_State ;
struct TYPE_34__ {int /*<<< orphan*/  value; } ;
struct TYPE_37__ {TYPE_2__ u; int /*<<< orphan*/ * v; } ;
typedef  TYPE_5__ UpVal ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_29__ {int tt; } ;
struct TYPE_38__ {TYPE_1__ gch; } ;
struct TYPE_35__ {TYPE_6__* gclist; } ;
struct TYPE_33__ {TYPE_3__ c; } ;
struct TYPE_32__ {TYPE_6__* gclist; } ;
struct TYPE_31__ {TYPE_6__* gclist; } ;
struct TYPE_30__ {TYPE_6__* gclist; } ;
struct TYPE_28__ {int /*<<< orphan*/ * env; int /*<<< orphan*/ * metatable; } ;
typedef  TYPE_6__ GCObject ;

/* Variables and functions */
#define  LUA_TFUNCTION 134 
#define  LUA_TPROTO 133 
#define  LUA_TSTRING 132 
#define  LUA_TTABLE 131 
#define  LUA_TTHREAD 130 
#define  LUA_TUPVAL 129 
#define  LUA_TUSERDATA 128 
 TYPE_26__* gco2cl (TYPE_6__*) ; 
 TYPE_24__* gco2h (TYPE_6__*) ; 
 TYPE_22__* gco2p (TYPE_6__*) ; 
 TYPE_20__* gco2th (TYPE_6__*) ; 
 TYPE_18__* gco2u (TYPE_6__*) ; 
 TYPE_5__* gco2uv (TYPE_6__*) ; 
 int /*<<< orphan*/  gray2black (TYPE_6__*) ; 
 int /*<<< orphan*/  isdead (TYPE_4__*,TYPE_6__*) ; 
 scalar_t__ iswhite (TYPE_6__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markobject (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markvalue (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  white2gray (TYPE_6__*) ; 

__attribute__((used)) static void reallymarkobject (global_State *g, GCObject *o) {
  lua_assert(iswhite(o) && !isdead(g, o));
  white2gray(o);
  switch (o->gch.tt) {
    case LUA_TSTRING: {
      return;
    }
    case LUA_TUSERDATA: {
      Table *mt = gco2u(o)->metatable;
      gray2black(o);  /* udata are never gray */
      if (mt) markobject(g, mt);
      markobject(g, gco2u(o)->env);
      return;
    }
    case LUA_TUPVAL: {
      UpVal *uv = gco2uv(o);
      markvalue(g, uv->v);
      if (uv->v == &uv->u.value)  /* closed? */
        gray2black(o);  /* open upvalues are never black */
      return;
    }
    case LUA_TFUNCTION: {
      gco2cl(o)->c.gclist = g->gray;
      g->gray = o;
      break;
    }
    case LUA_TTABLE: {
      gco2h(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    case LUA_TTHREAD: {
      gco2th(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    case LUA_TPROTO: {
      gco2p(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    default: lua_assert(0);
  }
}