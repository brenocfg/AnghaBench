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
 int EXIT_SUCCESS ; 
 scalar_t__ LUA_OK ; 
 int doargs (int,char**) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,char**) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmain ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char* argv[])
{
 lua_State* L;
 int i=doargs(argc,argv);
 argc-=i; argv+=i;
 if (argc<=0) usage("no input files given");
 L=luaL_newstate();
 if (L==NULL) fatal("cannot create state: not enough memory");
 lua_pushcfunction(L,&pmain);
 lua_pushinteger(L,argc);
 lua_pushlightuserdata(L,argv);
 if (lua_pcall(L,2,0,0)!=LUA_OK) fatal(lua_tostring(L,-1));
 lua_close(L);
 return EXIT_SUCCESS;
}