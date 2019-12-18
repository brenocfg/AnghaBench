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
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  TTree ;

/* Variables and functions */
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/ * newcharset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  treebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp_set (lua_State *L) {
  size_t l;
  const char *s = luaL_checklstring(L, 1, &l);
  TTree *tree = newcharset(L);
  while (l--) {
    setchar(treebuffer(tree), (byte)(*s));
    s++;
  }
  return 1;
}