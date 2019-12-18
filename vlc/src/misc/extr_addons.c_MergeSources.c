#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  (* addon_found ) (TYPE_4__*,TYPE_5__*) ;} ;
struct TYPE_17__ {TYPE_3__ owner; TYPE_2__* p_priv; } ;
typedef  TYPE_4__ addons_manager_t ;
typedef  int /*<<< orphan*/  addon_uuid_t ;
struct TYPE_18__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  e_flags; scalar_t__ psz_version; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_5__ addon_entry_t ;
struct TYPE_14__ {int /*<<< orphan*/  entries; } ;
struct TYPE_15__ {TYPE_1__ finder; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDON_UPDATABLE ; 
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  addon_entry_Release (TYPE_5__*) ; 
 TYPE_5__* getHeldEntryByUUID (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MergeSources( addons_manager_t *p_manager,
                          addon_entry_t **pp_addons, int i_count )
{
    addon_entry_t *p_entry, *p_manager_entry;
    addon_uuid_t zerouuid;
    memset( zerouuid, 0, sizeof( addon_uuid_t ) );
    for ( int i=0; i < i_count; i++ )
    {
        p_entry = pp_addons[i];
        vlc_mutex_lock( &p_entry->lock );
        if ( memcmp( p_entry->uuid, zerouuid, sizeof( addon_uuid_t ) ) )
            p_manager_entry = getHeldEntryByUUID( p_manager, p_entry->uuid );
        else
            p_manager_entry = NULL;
        if ( !p_manager_entry )
        {
            ARRAY_APPEND( p_manager->p_priv->finder.entries, p_entry );
            p_manager->owner.addon_found( p_manager, p_entry );
        }
        else
        {
            vlc_mutex_lock( &p_manager_entry->lock );
            if ( ( p_manager_entry->psz_version && p_entry->psz_version )
                 && /* FIXME: better version comparison */
                 strcmp( p_manager_entry->psz_version, p_entry->psz_version )
                 )
            {
                p_manager_entry->e_flags |= ADDON_UPDATABLE;
            }
            vlc_mutex_unlock( &p_manager_entry->lock );
            addon_entry_Release( p_manager_entry );
        }
        vlc_mutex_unlock( &p_entry->lock );
    }
}