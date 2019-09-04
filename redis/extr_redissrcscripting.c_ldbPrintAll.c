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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbLogStackValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_getlocal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_getstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

void ldbPrintAll(lua_State *lua) {
    lua_Debug ar;
    int vars = 0;

    if (lua_getstack(lua,0,&ar) != 0) {
        const char *name;
        int i = 1; /* Variable index. */
        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
            i++;
            if (!strstr(name,"(*temporary)")) {
                sds prefix = sdscatprintf(sdsempty(),"<value> %s = ",name);
                ldbLogStackValue(lua,prefix);
                sdsfree(prefix);
                vars++;
            }
            lua_pop(lua,1);
        }
    }

    if (vars == 0) {
        ldbLog(sdsnew("No local variables in the current context."));
    }
}