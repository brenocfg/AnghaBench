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
typedef  int /*<<< orphan*/  httpd_handler_t ;
struct TYPE_4__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ httpd_handler_lua_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* httpd_HandlerDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_httpd_handler_delete( lua_State *L )
{
    httpd_handler_t **pp_handler = (httpd_handler_t**)luaL_checkudata( L, 1, "httpd_handler" );
    httpd_handler_lua_t *p_sys = httpd_HandlerDelete( *pp_handler );
    luaL_unref( p_sys->L, LUA_REGISTRYINDEX, p_sys->ref );
    free( p_sys );
    return 0;
}