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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int (* member_1 ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  CJSON_MODNAME ; 
 int /*<<< orphan*/  CJSON_VERSION ; 
 int /*<<< orphan*/  fpconv_init () ; 
 int json_cfg_decode_invalid_numbers (int /*<<< orphan*/ *) ; 
 int json_cfg_decode_max_depth (int /*<<< orphan*/ *) ; 
 int json_cfg_encode_invalid_numbers (int /*<<< orphan*/ *) ; 
 int json_cfg_encode_keep_buffer (int /*<<< orphan*/ *) ; 
 int json_cfg_encode_max_depth (int /*<<< orphan*/ *) ; 
 int json_cfg_encode_number_precision (int /*<<< orphan*/ *) ; 
 int json_cfg_encode_sparse_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_create_config (int /*<<< orphan*/ *) ; 
 int json_decode (int /*<<< orphan*/ *) ; 
 int json_encode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_setfuncs (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int lua_cjson_new(lua_State *l)
{
    luaL_Reg reg[] = {
        { "encode", json_encode },
        { "decode", json_decode },
        { "encode_sparse_array", json_cfg_encode_sparse_array },
        { "encode_max_depth", json_cfg_encode_max_depth },
        { "decode_max_depth", json_cfg_decode_max_depth },
        { "encode_number_precision", json_cfg_encode_number_precision },
        { "encode_keep_buffer", json_cfg_encode_keep_buffer },
        { "encode_invalid_numbers", json_cfg_encode_invalid_numbers },
        { "decode_invalid_numbers", json_cfg_decode_invalid_numbers },
        { "new", lua_cjson_new },
        { NULL, NULL }
    };

    /* Initialise number conversions */
    fpconv_init();

    /* cjson module table */
    lua_newtable(l);

    /* Register functions with config data as upvalue */
    json_create_config(l);
    luaL_setfuncs(l, reg, 1);

    /* Set cjson.null */
    lua_pushlightuserdata(l, NULL);
    lua_setfield(l, -2, "null");

    /* Set module name / version fields */
    lua_pushliteral(l, CJSON_MODNAME);
    lua_setfield(l, -2, "_NAME");
    lua_pushliteral(l, CJSON_VERSION);
    lua_setfield(l, -2, "_VERSION");

    return 1;
}