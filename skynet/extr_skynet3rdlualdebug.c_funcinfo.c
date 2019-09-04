#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* source; int linedefined; int lastlinedefined; char* what; int /*<<< orphan*/  short_src; } ;
typedef  TYPE_3__ lua_Debug ;
struct TYPE_10__ {TYPE_1__* p; } ;
struct TYPE_13__ {TYPE_2__ l; } ;
struct TYPE_12__ {int linedefined; int lastlinedefined; scalar_t__ source; } ;
struct TYPE_9__ {TYPE_4__* sp; } ;
typedef  TYPE_4__ SharedProto ;
typedef  TYPE_5__ Closure ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_IDSIZE ; 
 char* getstr (scalar_t__) ; 
 int /*<<< orphan*/  luaO_chunkid (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ noLuaClosure (TYPE_5__*) ; 

__attribute__((used)) static void funcinfo (lua_Debug *ar, Closure *cl) {
  if (noLuaClosure(cl)) {
    ar->source = "=[C]";
    ar->linedefined = -1;
    ar->lastlinedefined = -1;
    ar->what = "C";
  }
  else {
    SharedProto *p = cl->l.p->sp;
    ar->source = p->source ? getstr(p->source) : "=?";
    ar->linedefined = p->linedefined;
    ar->lastlinedefined = p->lastlinedefined;
    ar->what = (ar->linedefined == 0) ? "main" : "Lua";
  }
  luaO_chunkid(ar->short_src, ar->source, LUA_IDSIZE);
}