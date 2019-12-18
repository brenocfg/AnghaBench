#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  intf_thread_t ;
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_7__ {TYPE_1__* p_sys; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_6__ {int /*<<< orphan*/ * L; int /*<<< orphan*/  dtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register_namespace (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaopen_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_dialog (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaopen_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_msg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_osd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_playlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_rand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_strings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_video (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_vlcio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_vlm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_volume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaopen_xml (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  p_reg ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * vlc_intf_GetMainPlaylist (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_object_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ vlclua_add_modules_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlclua_dofile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlclua_extension_deactivate ; 
 int /*<<< orphan*/  vlclua_extension_keep_alive ; 
 int /*<<< orphan*/  vlclua_extension_require ; 
 int /*<<< orphan*/  vlclua_extension_set (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlclua_fd_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ vlclua_fd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_set_playlist_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_set_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lua_State* GetLuaState( extensions_manager_t *p_mgr,
                               extension_t *p_ext )
{
    assert( p_ext != NULL );
    lua_State *L = p_ext->p_sys->L;

    if( !L )
    {
        L = luaL_newstate();
        if( !L )
        {
            msg_Err( p_mgr, "Could not create new Lua State" );
            return NULL;
        }
        vlclua_set_this( L, p_mgr );
        intf_thread_t *intf = (intf_thread_t *) vlc_object_parent(p_mgr);
        vlc_playlist_t *playlist = vlc_intf_GetMainPlaylist(intf);
        vlclua_set_playlist_internal(L, playlist);
        vlclua_extension_set( L, p_ext );

        luaL_openlibs( L );
        luaL_register_namespace( L, "vlc", p_reg );
        luaopen_msg( L );

        /* Load more libraries */
        luaopen_config( L );
        luaopen_dialog( L, p_ext );
        luaopen_input( L );
        luaopen_msg( L );
        if( vlclua_fd_init( L, &p_ext->p_sys->dtable ) )
        {
            lua_close( L );
            return NULL;
        }
        luaopen_object( L );
        luaopen_osd( L );
        luaopen_playlist( L );
        luaopen_stream( L );
        luaopen_strings( L );
        luaopen_variables( L );
        luaopen_video( L );
        luaopen_vlm( L );
        luaopen_volume( L );
        luaopen_xml( L );
        luaopen_vlcio( L );
        luaopen_errno( L );
        luaopen_rand( L );
#if defined(_WIN32) && !VLC_WINSTORE_APP
        luaopen_win( L );
#endif

        /* Register extension specific functions */
        lua_getglobal( L, "vlc" );
        lua_pushcfunction( L, vlclua_extension_deactivate );
        lua_setfield( L, -2, "deactivate" );
        lua_pushcfunction( L, vlclua_extension_keep_alive );
        lua_setfield( L, -2, "keep_alive" );

        /* Setup the module search path */
        if( !strncmp( p_ext->psz_name, "zip://", 6 ) )
        {
            /* Load all required modules manually */
            lua_register( L, "require", &vlclua_extension_require );
        }
        else
        {
            if( vlclua_add_modules_path( L, p_ext->psz_name ) )
            {
                msg_Warn( p_mgr, "Error while setting the module "
                          "search path for %s", p_ext->psz_name );
                vlclua_fd_cleanup( &p_ext->p_sys->dtable );
                lua_close( L );
                return NULL;
            }
        }
        /* Load and run the script(s) */
        if( vlclua_dofile( VLC_OBJECT( p_mgr ), L, p_ext->psz_name ) )
        {
            msg_Warn( p_mgr, "Error loading script %s: %s", p_ext->psz_name,
                      lua_tostring( L, lua_gettop( L ) ) );
            vlclua_fd_cleanup( &p_ext->p_sys->dtable );
            lua_close( L );
            return NULL;
        }

        p_ext->p_sys->L = L;
    }

    return L;
}