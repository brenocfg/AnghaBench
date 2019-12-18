#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  used_in ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* short_src; int linedefined; int lastlinedefined; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  MARKED_TABLE ; 
 int /*<<< orphan*/  RT_UPVALUE ; 
 int /*<<< orphan*/  is_marked (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 char* lua_getupvalue (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* lua_topointer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_root (int /*<<< orphan*/ *,void const*,char const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mark_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marked (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 

__attribute__((used)) static void mark_function(lua_State *L, lua_State *dL) {
	const void *p = lua_topointer(L, -1);
	int i;
	lua_Debug ar;
	char used_in[128];
	const char *name;
	
	
	if (!is_marked(dL, p)) {
		marked(dL, p, 0); //已经在table里头算了
		
		lua_pushvalue(L, -1);
		lua_getinfo(L, ">S", &ar);
		snprintf(used_in, sizeof(used_in) - 1, "%s:%d~%d", ar.short_src, ar.linedefined, ar.lastlinedefined);
		used_in[sizeof(used_in) - 1] = 0;
		
		for (i=1;;i++) {
			name = lua_getupvalue(L,-1,i);
			if (name == NULL)
				break;
			p = lua_topointer(L, -1);
			
			if (*name != '\0' && LUA_TTABLE == lua_type(L, -1)) {
				make_root(dL, p, name, RT_UPVALUE, used_in, 1);
				lua_insert(dL, MARKED_TABLE);
				mark_object(L, dL);
				lua_remove(dL, MARKED_TABLE);
			} else if (LUA_TFUNCTION == lua_type(L, -1)) {
				mark_function(L, dL);
			}
			lua_pop(L, 1);
		}
	}
}