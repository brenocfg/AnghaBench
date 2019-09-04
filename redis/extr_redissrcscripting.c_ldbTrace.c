#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  currentline; int /*<<< orphan*/  short_src; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbLogSourceLine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 scalar_t__ lua_getstack (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

void ldbTrace(lua_State *lua) {
    lua_Debug ar;
    int level = 0;

    while(lua_getstack(lua,level,&ar)) {
        lua_getinfo(lua,"Snl",&ar);
        if(strstr(ar.short_src,"user_script") != NULL) {
            ldbLog(sdscatprintf(sdsempty(),"%s %s:",
                (level == 0) ? "In" : "From",
                ar.name ? ar.name : "top level"));
            ldbLogSourceLine(ar.currentline);
        }
        level++;
    }
    if (level == 0) {
        ldbLog(sdsnew("<error> Can't retrieve Lua stack."));
    }
}