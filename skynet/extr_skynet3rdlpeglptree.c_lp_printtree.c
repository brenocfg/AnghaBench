#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TTree ;

/* Variables and functions */
 int /*<<< orphan*/  finalfix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getpatt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printktable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printtree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp_printtree (lua_State *L) {
  TTree *tree = getpatt(L, 1, NULL);
  int c = lua_toboolean(L, 2);
  if (c) {
    lua_getuservalue(L, 1);  /* push 'ktable' (may be used by 'finalfix') */
    finalfix(L, 0, NULL, tree);
    lua_pop(L, 1);  /* remove 'ktable' */
  }
  printktable(L, 1);
  printtree(tree, 0);
  return 0;
}