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
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,double) ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int pushresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g_write(lua_State*L,FILE*f,int arg){
int nargs=lua_gettop(L)-1;
int status=1;
for(;nargs--;arg++){
if(lua_type(L,arg)==3){
status=status&&
fprintf(f,"%.14g",lua_tonumber(L,arg))>0;
}
else{
size_t l;
const char*s=luaL_checklstring(L,arg,&l);
status=status&&(fwrite(s,sizeof(char),l,f)==l);
}
}
return pushresult(L,status,NULL);
}