#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {char* buffer; char* cursor; } ;
typedef  TYPE_1__ buffer ;

/* Variables and functions */
 char* buffer_pushlstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  buffer_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 

void script_response(lua_State *L, int status, buffer *headers, buffer *body) {
    lua_getglobal(L, "response");
    lua_pushinteger(L, status);
    lua_newtable(L);

    for (char *c = headers->buffer; c < headers->cursor; ) {
        c = buffer_pushlstring(L, c);
        c = buffer_pushlstring(L, c);
        lua_rawset(L, -3);
    }

    lua_pushlstring(L, body->buffer, body->cursor - body->buffer);
    lua_call(L, 3, 0);

    buffer_reset(headers);
    buffer_reset(body);
}