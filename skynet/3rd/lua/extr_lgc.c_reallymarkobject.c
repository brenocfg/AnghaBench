#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  gray; int /*<<< orphan*/  mainthread; int /*<<< orphan*/  GCmemtrav; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_26__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_25__ {int tt; } ;
struct TYPE_23__ {int /*<<< orphan*/  lnglen; } ;
struct TYPE_22__ {TYPE_1__ u; int /*<<< orphan*/  shrlen; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
#define  LUA_TCCL 135 
#define  LUA_TLCL 134 
#define  LUA_TLNGSTR 133 
#define  LUA_TPROTO 132 
#define  LUA_TSHRSTR 131 
#define  LUA_TTABLE 130 
#define  LUA_TTHREAD 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  gco2ccl (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2lcl (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2p (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2t (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2th (TYPE_3__*) ; 
 TYPE_15__* gco2ts (TYPE_3__*) ; 
 TYPE_5__* gco2u (TYPE_3__*) ; 
 TYPE_3__* gcvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getuservalue (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gray2black (TYPE_3__*) ; 
 scalar_t__ isshared (TYPE_3__*) ; 
 int /*<<< orphan*/  linkgclist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markobjectN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizelstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeudata (TYPE_5__*) ; 
 int /*<<< orphan*/  valiswhite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  white2gray (TYPE_3__*) ; 

__attribute__((used)) static void reallymarkobject (global_State *g, GCObject *o) {
 reentry:
  if (isshared(o))
    return;
  white2gray(o);
  switch (o->tt) {
    case LUA_TSHRSTR: {
      gray2black(o);
      g->GCmemtrav += sizelstring(gco2ts(o)->shrlen);
      break;
    }
    case LUA_TLNGSTR: {
      gray2black(o);
      g->GCmemtrav += sizelstring(gco2ts(o)->u.lnglen);
      break;
    }
    case LUA_TUSERDATA: {
      TValue uvalue;
      markobjectN(g, gco2u(o)->metatable);  /* mark its metatable */
      gray2black(o);
      g->GCmemtrav += sizeudata(gco2u(o));
      getuservalue(g->mainthread, gco2u(o), &uvalue);
      if (valiswhite(&uvalue)) {  /* markvalue(g, &uvalue); */
        o = gcvalue(&uvalue);
        goto reentry;
      }
      break;
    }
    case LUA_TLCL: {
      linkgclist(gco2lcl(o), g->gray);
      break;
    }
    case LUA_TCCL: {
      linkgclist(gco2ccl(o), g->gray);
      break;
    }
    case LUA_TTABLE: {
      linkgclist(gco2t(o), g->gray);
      break;
    }
    case LUA_TTHREAD: {
      linkgclist(gco2th(o), g->gray);
      break;
    }
    case LUA_TPROTO: {
      linkgclist(gco2p(o), g->gray);
      break;
    }
    default: lua_assert(0); break;
  }
}