#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_13__ {int no_interact; } ;
struct TYPE_17__ {int (* pf_catalog ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ obj; } ;
typedef  TYPE_5__ addons_storage_t ;
struct TYPE_18__ {TYPE_4__* p_priv; } ;
typedef  TYPE_6__ addons_manager_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_size; int /*<<< orphan*/  p_elems; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; TYPE_2__ entries; } ;
struct TYPE_16__ {TYPE_3__ finder; int /*<<< orphan*/  p_parent; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/ * module_need (TYPE_5__*,char*,char*,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_5__*) ; 

__attribute__((used)) static int addons_manager_WriteCatalog( addons_manager_t *p_manager )
{
    int i_return = VLC_EGENERIC;

    addons_storage_t *p_storage =
        vlc_custom_create( p_manager->p_priv->p_parent, sizeof( *p_storage ), "entries storage" );
    p_storage->obj.no_interact = true;

    module_t *p_module = module_need( p_storage, "addons storage",
                                      "addons.store.install", true );
    if( p_module )
    {
        vlc_mutex_lock( &p_manager->p_priv->finder.lock );
        i_return = p_storage->pf_catalog( p_storage, p_manager->p_priv->finder.entries.p_elems,
                                          p_manager->p_priv->finder.entries.i_size );
        vlc_mutex_unlock( &p_manager->p_priv->finder.lock );
        module_unneed( p_storage, p_module );
    }
    vlc_object_delete(p_storage);

    return i_return;
}