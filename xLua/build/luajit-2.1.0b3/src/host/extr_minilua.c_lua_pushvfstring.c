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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaC_checkGC (int /*<<< orphan*/ *) ; 
 char* luaO_pushvfstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*lua_pushvfstring(lua_State*L,const char*fmt,
va_list argp){
const char*ret;
luaC_checkGC(L);
ret=luaO_pushvfstring(L,fmt,argp);
return ret;
}