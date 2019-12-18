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
struct vlclua_playlist {int /*<<< orphan*/  filename; int /*<<< orphan*/ * L; } ;
struct TYPE_6__ {int /*<<< orphan*/ * psz_url; struct vlclua_playlist* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int VLC_ENOITEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetURL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_SetURL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register_namespace (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  p_reg_parse ; 
 int /*<<< orphan*/ * vlclua_read_input_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ReadDir(stream_t *s, input_item_node_t *node)
{
    struct vlclua_playlist *sys = s->p_sys;
    lua_State *L = sys->L;

    luaL_register_namespace( L, "vlc", p_reg_parse );

    lua_getglobal( L, "parse" );

    if( !lua_isfunction( L, -1 ) )
    {
        msg_Warn(s, "error running script %s: function %s(): %s",
                 sys->filename, "parse", "not found");
        return VLC_ENOITEM;
    }

    if( lua_pcall( L, 0, 1, 0 ) )
    {
        msg_Warn(s, "error running script %s: function %s(): %s",
                 sys->filename, "parse", lua_tostring(L, lua_gettop(L)));
        return VLC_ENOITEM;
    }

    if (!lua_gettop(L))
    {
        msg_Err(s, "script went completely foobar");
        return VLC_ENOITEM;
    }

    if (!lua_istable(L, -1))
    {
        msg_Warn(s, "Playlist should be a table.");
        return VLC_ENOITEM;
    }

    lua_pushnil(L);

    /* playlist nil */
    while (lua_next(L, -2))
    {
        input_item_t *item = vlclua_read_input_item(VLC_OBJECT(s), L);
        if (item != NULL)
        {
            /* copy the original URL to the meta data,
             * if "URL" is still empty */
            char *url = input_item_GetURL(item);
            if (url == NULL && s->psz_url != NULL)
                input_item_SetURL(item, s->psz_url);
            free(url);

            input_item_node_AppendItem(node, item);
            input_item_Release(item);
        }
        /* pop the value, keep the key for the next lua_next() call */
        lua_pop(L, 1);
    }
    /* playlist */

    return VLC_SUCCESS;
}