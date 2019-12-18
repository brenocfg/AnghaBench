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

/* Variables and functions */
 int /*<<< orphan*/  ldbLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldbLogStackValue (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_loadbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatsds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsjoinsds (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 

void ldbEval(lua_State *lua, sds *argv, int argc) {
    /* Glue the script together if it is composed of multiple arguments. */
    sds code = sdsjoinsds(argv+1,argc-1," ",1);
    sds expr = sdscatsds(sdsnew("return "),code);

    /* Try to compile it as an expression, prepending "return ". */
    if (luaL_loadbuffer(lua,expr,sdslen(expr),"@ldb_eval")) {
        lua_pop(lua,1);
        /* Failed? Try as a statement. */
        if (luaL_loadbuffer(lua,code,sdslen(code),"@ldb_eval")) {
            ldbLog(sdscatfmt(sdsempty(),"<error> %s",lua_tostring(lua,-1)));
            lua_pop(lua,1);
            sdsfree(code);
            return;
        }
    }

    /* Call it. */
    sdsfree(code);
    sdsfree(expr);
    if (lua_pcall(lua,0,1,0)) {
        ldbLog(sdscatfmt(sdsempty(),"<error> %s",lua_tostring(lua,-1)));
        lua_pop(lua,1);
        return;
    }
    ldbLogStackValue(lua,"<retval> ");
    lua_pop(lua,1);
}