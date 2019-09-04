#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_7__ {char* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_8__ {int /*<<< orphan*/  lua_scripts_mem; int /*<<< orphan*/ * lua_client; int /*<<< orphan*/  lua_scripts; } ;

/* Variables and functions */
 int DICT_OK ; 
 int /*<<< orphan*/  addReplyErrorFormat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int dictAdd (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,char*) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 scalar_t__ getStringObjectSdsUsedMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_1__*) ; 
 scalar_t__ luaL_loadbuffer (int /*<<< orphan*/ *,char*,int,char*) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sdsZmallocSize (char*) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatlen (char*,char*,int) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int sdslen (char*) ; 
 char* sdsnewlen (char*,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sha1hex (char*,char*,int) ; 

sds luaCreateFunction(client *c, lua_State *lua, robj *body) {
    char funcname[43];
    dictEntry *de;

    funcname[0] = 'f';
    funcname[1] = '_';
    sha1hex(funcname+2,body->ptr,sdslen(body->ptr));

    sds sha = sdsnewlen(funcname+2,40);
    if ((de = dictFind(server.lua_scripts,sha)) != NULL) {
        sdsfree(sha);
        return dictGetKey(de);
    }

    sds funcdef = sdsempty();
    funcdef = sdscat(funcdef,"function ");
    funcdef = sdscatlen(funcdef,funcname,42);
    funcdef = sdscatlen(funcdef,"() ",3);
    funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
    funcdef = sdscatlen(funcdef,"\nend",4);

    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
        if (c != NULL) {
            addReplyErrorFormat(c,
                "Error compiling script (new function): %s\n",
                lua_tostring(lua,-1));
        }
        lua_pop(lua,1);
        sdsfree(sha);
        sdsfree(funcdef);
        return NULL;
    }
    sdsfree(funcdef);

    if (lua_pcall(lua,0,0,0)) {
        if (c != NULL) {
            addReplyErrorFormat(c,"Error running script (new function): %s\n",
                lua_tostring(lua,-1));
        }
        lua_pop(lua,1);
        sdsfree(sha);
        return NULL;
    }

    /* We also save a SHA1 -> Original script map in a dictionary
     * so that we can replicate / write in the AOF all the
     * EVALSHA commands as EVAL using the original script. */
    int retval = dictAdd(server.lua_scripts,sha,body);
    serverAssertWithInfo(c ? c : server.lua_client,NULL,retval == DICT_OK);
    server.lua_scripts_mem += sdsZmallocSize(sha) + getStringObjectSdsUsedMemory(body);
    incrRefCount(body);
    return sha;
}