#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* openupval; struct TYPE_12__* twups; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_13__ {TYPE_3__* twups; } ;
typedef  TYPE_4__ global_State ;
struct TYPE_10__ {scalar_t__ touched; TYPE_5__* next; } ;
struct TYPE_11__ {TYPE_1__ open; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  v; } ;
typedef  TYPE_5__ UpVal ;

/* Variables and functions */
 int /*<<< orphan*/  isblack (TYPE_3__*) ; 
 scalar_t__ isgray (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markvalue (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remarkupvals (global_State *g) {
  lua_State *thread;
  lua_State **p = &g->twups;
  while ((thread = *p) != NULL) {
    lua_assert(!isblack(thread));  /* threads are never black */
    if (isgray(thread) && thread->openupval != NULL)
      p = &thread->twups;  /* keep marked thread with upvalues in the list */
    else {  /* thread is not marked or without upvalues */
      UpVal *uv;
      *p = thread->twups;  /* remove thread from the list */
      thread->twups = thread;  /* mark that it is out of list */
      for (uv = thread->openupval; uv != NULL; uv = uv->u.open.next) {
        if (uv->u.open.touched) {
          markvalue(g, uv->v);  /* remark upvalue's value */
          uv->u.open.touched = 0;
        }
      }
    }
  }
}