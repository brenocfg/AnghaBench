#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* member_0; char* member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ table_field ;
struct http_parser_url {int field_set; TYPE_1__* field_data; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {size_t off; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  LUA_TSTRING ; 
 int /*<<< orphan*/  UF_HOST ; 
 int UF_PATH ; 
 int /*<<< orphan*/  UF_PORT ; 
 int /*<<< orphan*/  UF_SCHEMA ; 
 int /*<<< orphan*/  addrlib ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 scalar_t__ luaL_dofile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_dostring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_url_part (int /*<<< orphan*/ *,char*,struct http_parser_url*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_parse_url (char*,struct http_parser_url*) ; 
 char* script_wrk_connect ; 
 char* script_wrk_lookup ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fields (int /*<<< orphan*/ *,int,TYPE_2__ const*) ; 
 int /*<<< orphan*/  statslib ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  threadlib ; 

lua_State *script_create(char *file, char *url, char **headers) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    (void) luaL_dostring(L, "wrk = require \"wrk\"");

    luaL_newmetatable(L, "wrk.addr");
    luaL_register(L, NULL, addrlib);
    luaL_newmetatable(L, "wrk.stats");
    luaL_register(L, NULL, statslib);
    luaL_newmetatable(L, "wrk.thread");
    luaL_register(L, NULL, threadlib);

    struct http_parser_url parts = {};
    script_parse_url(url, &parts);
    char *path = "/";

    if (parts.field_set & (1 << UF_PATH)) {
        path = &url[parts.field_data[UF_PATH].off];
    }

    const table_field fields[] = {
        { "lookup",  LUA_TFUNCTION, script_wrk_lookup  },
        { "connect", LUA_TFUNCTION, script_wrk_connect },
        { "path",    LUA_TSTRING,   path               },
        { NULL,      0,             NULL               },
    };

    lua_getglobal(L, "wrk");

    set_field(L, 4, "scheme", push_url_part(L, url, &parts, UF_SCHEMA));
    set_field(L, 4, "host",   push_url_part(L, url, &parts, UF_HOST));
    set_field(L, 4, "port",   push_url_part(L, url, &parts, UF_PORT));
    set_fields(L, 4, fields);

    lua_getfield(L, 4, "headers");
    for (char **h = headers; *h; h++) {
        char *p = strchr(*h, ':');
        if (p && p[1] == ' ') {
            lua_pushlstring(L, *h, p - *h);
            lua_pushstring(L, p + 2);
            lua_settable(L, 5);
        }
    }
    lua_pop(L, 5);

    if (file && luaL_dofile(L, file)) {
        const char *cause = lua_tostring(L, -1);
        fprintf(stderr, "%s: %s\n", file, cause);
    }

    return L;
}