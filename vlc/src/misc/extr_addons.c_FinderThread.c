#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_20__ {int /*<<< orphan*/  (* discovery_ended ) (TYPE_5__*) ;} ;
struct TYPE_23__ {TYPE_4__* p_priv; TYPE_2__ owner; } ;
typedef  TYPE_5__ addons_manager_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_size; int /*<<< orphan*/  p_elems; } ;
struct TYPE_19__ {int no_interact; } ;
struct TYPE_24__ {char* psz_uri; TYPE_14__ entries; int /*<<< orphan*/  (* pf_find ) (TYPE_6__*) ;TYPE_1__ obj; } ;
typedef  TYPE_6__ addons_finder_t ;
struct TYPE_18__ {scalar_t__ i_size; char** p_elems; } ;
struct TYPE_21__ {int /*<<< orphan*/  lock; TYPE_15__ uris; scalar_t__ b_live; int /*<<< orphan*/  waitcond; int /*<<< orphan*/  p_interrupt; } ;
struct TYPE_22__ {TYPE_3__ finder; int /*<<< orphan*/  p_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (TYPE_14__) ; 
 int /*<<< orphan*/  ARRAY_REMOVE (TYPE_15__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_RESET (TYPE_14__) ; 
 int /*<<< orphan*/  MergeSources (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finder_thread_interrupted ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * module_need (TYPE_6__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_interrupt_register (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_interrupt_unregister () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_6__*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *FinderThread( void *p_data )
{
    addons_manager_t *p_manager = p_data;
    int i_cancel = vlc_savecancel();
    vlc_interrupt_set( p_manager->p_priv->finder.p_interrupt );

    vlc_mutex_lock( &p_manager->p_priv->finder.lock );
    while( p_manager->p_priv->finder.b_live )
    {
        char *psz_uri;

        vlc_interrupt_register( finder_thread_interrupted, p_data );
        while( p_manager->p_priv->finder.uris.i_size == 0 &&
               p_manager->p_priv->finder.b_live )
        {
            vlc_cond_wait( &p_manager->p_priv->finder.waitcond,
                           &p_manager->p_priv->finder.lock );
        }
        vlc_interrupt_unregister();
        if( !p_manager->p_priv->finder.b_live )
            break;
        psz_uri = p_manager->p_priv->finder.uris.p_elems[0];
        ARRAY_REMOVE( p_manager->p_priv->finder.uris, 0 );

        vlc_mutex_unlock( &p_manager->p_priv->finder.lock );

        addons_finder_t *p_finder =
                vlc_custom_create( p_manager->p_priv->p_parent, sizeof( *p_finder ), "entries finder" );

        if( p_finder != NULL )
        {
            p_finder->obj.no_interact = true;
            module_t *p_module;
            ARRAY_INIT( p_finder->entries );
            p_finder->psz_uri = psz_uri;

            p_module = module_need( p_finder, "addons finder", NULL, false );
            if( p_module )
            {
                p_finder->pf_find( p_finder );
                module_unneed( p_finder, p_module );
                MergeSources( p_manager, p_finder->entries.p_elems, p_finder->entries.i_size );
            }
            ARRAY_RESET( p_finder->entries );
            free( psz_uri );
            vlc_object_delete(p_finder);
        }

        p_manager->owner.discovery_ended( p_manager );
        vlc_mutex_lock( &p_manager->p_priv->finder.lock );
    }

    vlc_mutex_unlock( &p_manager->p_priv->finder.lock );
    vlc_restorecancel( i_cancel );
    return NULL;
}