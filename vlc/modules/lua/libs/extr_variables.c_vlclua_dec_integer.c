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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DecInteger (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int vlclua_dec_integer( lua_State *L )
{
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );
    int64_t i_val = var_DecInteger( *pp_obj, psz_var );

    lua_pushinteger( L, i_val );
    return 1;
}