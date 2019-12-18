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
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  tag_error (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static const char*luaL_checklstring(lua_State*L,int narg,size_t*len){
const char*s=lua_tolstring(L,narg,len);
if(!s)tag_error(L,narg,4);
return s;
}