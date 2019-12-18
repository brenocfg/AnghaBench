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

/* Variables and functions */
 char* luaL_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int print(lua_State *L)
{
 int n=lua_gettop(L);
 int i;
 for (i=1; i<=n; i++)
 {
  if (i>1) printf("\t");
  if (lua_isstring(L,i))
   printf("%s",lua_tostring(L,i));
  else if (lua_isnil(L,i))
   printf("%s","nil");
  else if (lua_isboolean(L,i))
   printf("%s",lua_toboolean(L,i) ? "true" : "false");
  else
   printf("%s:%p",luaL_typename(L,i),lua_topointer(L,i));
 }
 printf("\n");
 return 0;
}