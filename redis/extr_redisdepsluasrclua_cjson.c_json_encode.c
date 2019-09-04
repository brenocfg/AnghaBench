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
typedef  int /*<<< orphan*/  strbuf_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  encode_keep_buffer; int /*<<< orphan*/  encode_buf; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_append_data (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* json_fetch_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 
 char* strbuf_string (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int json_encode(lua_State *l)
{
    json_config_t *cfg = json_fetch_config(l);
    strbuf_t local_encode_buf;
    strbuf_t *encode_buf;
    char *json;
    int len;

    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    if (!cfg->encode_keep_buffer) {
        /* Use private buffer */
        encode_buf = &local_encode_buf;
        strbuf_init(encode_buf, 0);
    } else {
        /* Reuse existing buffer */
        encode_buf = &cfg->encode_buf;
        strbuf_reset(encode_buf);
    }

    json_append_data(l, cfg, 0, encode_buf);
    json = strbuf_string(encode_buf, &len);

    lua_pushlstring(l, json, len);

    if (!cfg->encode_keep_buffer)
        strbuf_free(encode_buf);

    return 1;
}