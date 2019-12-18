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
 int /*<<< orphan*/  ADD_ERRNO_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

void luaopen_errno( lua_State *L )
{
    lua_newtable( L );

#define ADD_ERRNO_VALUE( value )  \
    lua_pushinteger( L, value );  \
    lua_setfield( L, -2, #value );

    ADD_ERRNO_VALUE( ENOENT );
    ADD_ERRNO_VALUE( EEXIST );
    ADD_ERRNO_VALUE( EACCES );
    ADD_ERRNO_VALUE( EINVAL );

#undef ADD_ERRNO_VALUE

    lua_setfield( L, -2, "errno" );
}