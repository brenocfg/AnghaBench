#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlclua_playlist {int /*<<< orphan*/ * L; int /*<<< orphan*/  filename; int /*<<< orphan*/ * access; int /*<<< orphan*/ * path; } ;
struct TYPE_6__ {struct vlclua_playlist* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  luabatch_context_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register_namespace (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  luaopen_msg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_strings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_xml (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char const*,...) ; 
 int /*<<< orphan*/  p_reg ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ vlclua_add_modules_path (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ vlclua_dofile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlclua_set_this (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int probe_luascript(vlc_object_t *obj, const char *filename,
                           const luabatch_context_t *ctx)
{
    stream_t *s = (stream_t *)obj;
    struct vlclua_playlist *sys = s->p_sys;

    /* Initialise Lua state structure */
    lua_State *L = luaL_newstate();
    if( !L )
        return VLC_ENOMEM;

    sys->L = L;

    /* Load Lua libraries */
    luaL_openlibs( L ); /* FIXME: Don't open all the libs? */

    vlclua_set_this(L, s);
    luaL_register_namespace( L, "vlc", p_reg );
    luaopen_msg( L );
    luaopen_strings( L );
    luaopen_stream( L );
    luaopen_variables( L );
    luaopen_xml( L );

    if (sys->path != NULL)
        lua_pushstring(L, sys->path);
    else
        lua_pushnil(L);
    lua_setfield( L, -2, "path" );

    if (sys->access != NULL)
        lua_pushstring(L, sys->access);
    else
        lua_pushnil(L);
    lua_setfield( L, -2, "access" );

    lua_pop( L, 1 );

    /* Setup the module search path */
    if (vlclua_add_modules_path(L, filename))
    {
        msg_Warn(s, "error setting the module search path for %s", filename);
        goto error;
    }

    /* Load and run the script(s) */
    if (vlclua_dofile(VLC_OBJECT(s), L, filename))
    {
        msg_Warn(s, "error loading script %s: %s", filename,
                 lua_tostring(L, lua_gettop(L)));
        goto error;
    }

    lua_getglobal( L, "probe" );
    if( !lua_isfunction( L, -1 ) )
    {
        msg_Warn(s, "error running script %s: function %s(): %s",
                 filename, "probe", "not found");
        goto error;
    }

    if( lua_pcall( L, 0, 1, 0 ) )
    {
        msg_Warn(s, "error running script %s: function %s(): %s",
                 filename, "probe", lua_tostring(L, lua_gettop(L)));
        goto error;
    }

    if( lua_gettop( L ) )
    {
        if( lua_toboolean( L, 1 ) )
        {
            msg_Dbg(s, "Lua playlist script %s's "
                    "probe() function was successful", filename );
            lua_pop( L, 1 );
            sys->filename = strdup(filename);
            return VLC_SUCCESS;
        }
    }

    (void) ctx;
error:
    lua_pop( L, 1 );
    lua_close(sys->L);
    return VLC_EGENERIC;
}