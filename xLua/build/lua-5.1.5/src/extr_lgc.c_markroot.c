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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  gcstate; int /*<<< orphan*/  mainthread; int /*<<< orphan*/ * weak; int /*<<< orphan*/ * grayagain; int /*<<< orphan*/ * gray; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSpropagate ; 
 int /*<<< orphan*/  gt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markmt (TYPE_1__*) ; 
 int /*<<< orphan*/  markobject (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markvalue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void markroot (lua_State *L) {
  global_State *g = G(L);
  g->gray = NULL;
  g->grayagain = NULL;
  g->weak = NULL;
  markobject(g, g->mainthread);
  /* make global table be traversed before main stack */
  markvalue(g, gt(g->mainthread));
  markvalue(g, registry(L));
  markmt(g);
  g->gcstate = GCSpropagate;
}