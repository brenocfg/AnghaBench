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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_item; } ;
typedef  TYPE_1__ luabatch_context_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  input_item_SetArtURL (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,TYPE_1__ const*) ; 

__attribute__((used)) static int fetch_art( vlc_object_t *p_this, const char * psz_filename,
                      const luabatch_context_t *p_context )
{
    lua_State *L = init( p_this, p_context->p_item, psz_filename );
    if( !L )
        return VLC_EGENERIC;

    int i_ret = run(p_this, psz_filename, L, "fetch_art", p_context);
    if(i_ret != VLC_SUCCESS)
    {
        lua_close( L );
        return i_ret;
    }

    if(lua_gettop( L ))
    {
        const char * psz_value;

        if( lua_isstring( L, -1 ) )
        {
            psz_value = lua_tostring( L, -1 );
            if( psz_value && *psz_value != 0 )
            {
                lua_Dbg( p_this, "setting arturl: %s", psz_value );
                input_item_SetArtURL ( p_context->p_item, psz_value );
                lua_close( L );
                return VLC_SUCCESS;
            }
        }
        else if( !lua_isnoneornil( L, -1 ) )
        {
            msg_Err( p_this, "Lua art fetcher script %s: "
                 "didn't return a string", psz_filename );
        }
    }
    else
    {
        msg_Err( p_this, "Script went completely foobar" );
    }

    lua_close( L );
    return VLC_EGENERIC;
}