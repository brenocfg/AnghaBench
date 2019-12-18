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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * vlc_alloc (size_t,int) ; 

__attribute__((used)) static uint8_t *vlclua_todata( lua_State *L, int narg, int *pi_data )
{
    size_t i_data;
    const char *psz_data = lua_tolstring( L, narg, &i_data );
    uint8_t *p_data = vlc_alloc( i_data, sizeof(uint8_t) );
    *pi_data = (int)i_data;
    if( !p_data )
    {
        luaL_error( L, "Error while allocating buffer." );
        return NULL; /* To please gcc even though luaL_error longjmp-ed out of here */
    }
    memcpy( p_data, psz_data, i_data );
    return p_data;
}