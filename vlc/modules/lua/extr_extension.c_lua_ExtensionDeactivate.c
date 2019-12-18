#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_8__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_9__ {int /*<<< orphan*/  event_manager; } ;
struct TYPE_7__ {int b_activated; int i_capabilities; int /*<<< orphan*/ * L; TYPE_6__* p_item; int /*<<< orphan*/  dtable; } ;

/* Variables and functions */
 int EXT_META_LISTENER ; 
 int /*<<< orphan*/  LUA_END ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  inputItemMetaChanged ; 
 int /*<<< orphan*/  input_item_Release (TYPE_6__*) ; 
 int lua_ExecuteFunction (int /*<<< orphan*/ *,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_InputItemMetaChanged ; 
 int /*<<< orphan*/  vlc_event_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vlclua_fd_interrupt (int /*<<< orphan*/ *) ; 

int lua_ExtensionDeactivate( extensions_manager_t *p_mgr, extension_t *p_ext )
{
    assert( p_mgr != NULL && p_ext != NULL );

    if( p_ext->p_sys->b_activated == false )
        return VLC_SUCCESS;

    vlclua_fd_interrupt( &p_ext->p_sys->dtable );

    // Unset and release input objects
    if( p_ext->p_sys->p_item )
    {
        if( p_ext->p_sys->i_capabilities & EXT_META_LISTENER )
            vlc_event_detach( &p_ext->p_sys->p_item->event_manager,
                              vlc_InputItemMetaChanged,
                              inputItemMetaChanged,
                              p_ext );
        input_item_Release(p_ext->p_sys->p_item);
        p_ext->p_sys->p_item = NULL;
    }

    int i_ret = lua_ExecuteFunction( p_mgr, p_ext, "deactivate", LUA_END );

    if ( p_ext->p_sys->L == NULL )
        return VLC_EGENERIC;
    lua_close( p_ext->p_sys->L );
    p_ext->p_sys->L = NULL;

    return i_ret;
}