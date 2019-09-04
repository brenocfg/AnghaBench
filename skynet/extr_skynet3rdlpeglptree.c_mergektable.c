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
 int concattable (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  correctkeys (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mergektable (lua_State *L, int idx, TTree *stree) {
  int n;
  lua_getuservalue(L, -1);  /* get ktables */
  lua_getuservalue(L, idx);
  n = concattable(L, -1, -2);
  lua_pop(L, 2);  /* remove both ktables */
  correctkeys(stree, n);
}