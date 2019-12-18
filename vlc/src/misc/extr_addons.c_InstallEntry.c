#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* p_priv; } ;
typedef  TYPE_3__ addons_manager_t ;
struct TYPE_12__ {scalar_t__ e_type; } ;
typedef  TYPE_4__ addon_entry_t ;
struct TYPE_9__ {int b_live; int /*<<< orphan*/  waitcond; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; int /*<<< orphan*/  entries; } ;
struct TYPE_10__ {TYPE_1__ installer; int /*<<< orphan*/  p_parent; } ;

/* Variables and functions */
 scalar_t__ ADDON_OTHER ; 
 scalar_t__ ADDON_PLUGIN ; 
 scalar_t__ ADDON_UNKNOWN ; 
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  InstallerThread ; 
 int VLC_EBADVAR ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int InstallEntry( addons_manager_t *p_manager, addon_entry_t *p_entry )
{
    if ( p_entry->e_type == ADDON_UNKNOWN ||
         p_entry->e_type == ADDON_PLUGIN ||
         p_entry->e_type == ADDON_OTHER )
        return VLC_EBADVAR;

    vlc_mutex_lock( &p_manager->p_priv->installer.lock );
    ARRAY_APPEND( p_manager->p_priv->installer.entries, p_entry );
    if( !p_manager->p_priv->installer.b_live )
    {
        if( vlc_clone( &p_manager->p_priv->installer.thread, InstallerThread, p_manager,
                       VLC_THREAD_PRIORITY_LOW ) )
        {
            msg_Err( p_manager->p_priv->p_parent,
                     "cannot spawn addons installer thread" );
            vlc_mutex_unlock( &p_manager->p_priv->installer.lock );
            return VLC_EGENERIC;
        }
        else
            p_manager->p_priv->installer.b_live = true;
    }
    vlc_mutex_unlock( &p_manager->p_priv->installer.lock );
    vlc_cond_signal( &p_manager->p_priv->installer.waitcond );
    return VLC_SUCCESS;
}