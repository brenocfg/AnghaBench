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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  aux_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int read_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_readline(lua_State*L){
FILE*f=*(FILE**)lua_touserdata(L,lua_upvalueindex(1));
int sucess;
if(f==NULL)
luaL_error(L,"file is already closed");
sucess=read_line(L,f);
if(ferror(f))
return luaL_error(L,"%s",strerror(errno));
if(sucess)return 1;
else{
if(lua_toboolean(L,lua_upvalueindex(2))){
lua_settop(L,0);
lua_pushvalue(L,lua_upvalueindex(1));
aux_close(L);
}
return 0;
}
}