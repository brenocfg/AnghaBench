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
typedef  int /*<<< orphan*/  lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbLogStackValue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 char* lua_getlocal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_getstack (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

void ldbPrint(lua_State *lua, char *varname) {
    lua_Debug ar;

    int l = 0; /* Stack level. */
    while (lua_getstack(lua,l,&ar) != 0) {
        l++;
        const char *name;
        int i = 1; /* Variable index. */
        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
            i++;
            if (strcmp(varname,name) == 0) {
                ldbLogStackValue(lua,"<value> ");
                lua_pop(lua,1);
                return;
            } else {
                lua_pop(lua,1); /* Discard the var name on the stack. */
            }
        }
    }

    /* Let's try with global vars in two selected cases */
    if (!strcmp(varname,"ARGV") || !strcmp(varname,"KEYS")) {
        lua_getglobal(lua, varname);
        ldbLogStackValue(lua,"<value> ");
        lua_pop(lua,1);
    } else {
        ldbLog(sdsnew("No such variable."));
    }
}