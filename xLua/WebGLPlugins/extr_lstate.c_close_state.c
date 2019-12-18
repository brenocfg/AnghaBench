#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  stack; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  size; int /*<<< orphan*/  hash; } ;
struct TYPE_16__ {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* frealloc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;TYPE_1__ strt; scalar_t__ version; } ;
typedef  TYPE_3__ global_State ;
typedef  int /*<<< orphan*/  LG ;

/* Variables and functions */
 TYPE_3__* G (TYPE_2__*) ; 
 int /*<<< orphan*/  freestack (TYPE_2__*) ; 
 int /*<<< orphan*/  fromstate (TYPE_2__*) ; 
 int gettotalbytes (TYPE_3__*) ; 
 int /*<<< orphan*/  luaC_freeallobjects (TYPE_2__*) ; 
 int /*<<< orphan*/  luaF_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_freearray (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  luai_userstateclose (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_state (lua_State *L) {
  global_State *g = G(L);
  luaF_close(L, L->stack);  /* close all upvalues for this thread */
  luaC_freeallobjects(L);  /* collect all objects */
  if (g->version)  /* closing a fully built state? */
    luai_userstateclose(L);
  luaM_freearray(L, G(L)->strt.hash, G(L)->strt.size);
  freestack(L);
  lua_assert(gettotalbytes(g) == sizeof(LG));
  (*g->frealloc)(g->ud, fromstate(L), sizeof(LG), 0);  /* free main block */
}