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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlclua_directory_stream_new ; 
 int /*<<< orphan*/  vlclua_memory_stream_new ; 
 int /*<<< orphan*/  vlclua_stream_new ; 

void luaopen_stream( lua_State *L )
{
    lua_pushcfunction( L, vlclua_stream_new );
    lua_setfield( L, -2, "stream" );
    lua_pushcfunction( L, vlclua_memory_stream_new );
    lua_setfield( L, -2, "memory_stream" );
    lua_pushcfunction( L, vlclua_directory_stream_new );
    lua_setfield( L, -2, "directory_stream" );
}