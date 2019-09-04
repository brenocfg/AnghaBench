#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/ * tree; scalar_t__ codesize; int /*<<< orphan*/ * code; } ;
typedef  int /*<<< orphan*/  TTree ;
typedef  TYPE_1__ Pattern ;

/* Variables and functions */
 int /*<<< orphan*/  PATTERN_T ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setuservalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static TTree *newtree (lua_State *L, int len) {
  size_t size = (len - 1) * sizeof(TTree) + sizeof(Pattern);
  Pattern *p = (Pattern *)lua_newuserdata(L, size);
  luaL_getmetatable(L, PATTERN_T);
  lua_pushvalue(L, -1);
  lua_setuservalue(L, -3);
  lua_setmetatable(L, -2);
  p->code = NULL;  p->codesize = 0;
  return p->tree;
}