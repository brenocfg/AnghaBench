#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct http_parser_url {int field_set; TYPE_1__* field_data; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  enum http_parser_url_fields { ____Placeholder_http_parser_url_fields } http_parser_url_fields ;
struct TYPE_2__ {size_t off; size_t len; } ;

/* Variables and functions */
#define  LUA_TNIL 129 
#define  LUA_TSTRING 128 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int push_url_part(lua_State *L, char *url, struct http_parser_url *parts, enum http_parser_url_fields field) {
    int type = parts->field_set & (1 << field) ? LUA_TSTRING : LUA_TNIL;
    uint16_t off, len;
    switch (type) {
        case LUA_TSTRING:
            off = parts->field_data[field].off;
            len = parts->field_data[field].len;
            lua_pushlstring(L, &url[off], len);
            break;
        case LUA_TNIL:
            lua_pushnil(L);
    }
    return type;
}