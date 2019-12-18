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
 int /*<<< orphan*/  createmeta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createstdfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  io_fclose ; 
 int /*<<< orphan*/  io_noclose ; 
 int /*<<< orphan*/  io_pclose ; 
 int /*<<< orphan*/  iolib ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  newfenv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int luaopen_io(lua_State*L){
createmeta(L);
newfenv(L,io_fclose);
lua_replace(L,(-10001));
luaL_register(L,"io",iolib);
newfenv(L,io_noclose);
createstdfile(L,stdin,1,"stdin");
createstdfile(L,stdout,2,"stdout");
createstdfile(L,stderr,0,"stderr");
lua_pop(L,1);
lua_getfield(L,-1,"popen");
newfenv(L,io_pclose);
lua_setfenv(L,-2);
lua_pop(L,1);
return 1;
}