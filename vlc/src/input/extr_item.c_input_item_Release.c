#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int i_options; int i_es; int i_epg; int i_categories; int i_slaves; int /*<<< orphan*/  lock; TYPE_2__** pp_slaves; TYPE_2__** pp_categories; TYPE_2__** pp_epg; TYPE_2__** es; TYPE_2__* optflagv; TYPE_2__** ppsz_options; TYPE_2__* opaques; int /*<<< orphan*/ * p_meta; TYPE_2__* p_stats; TYPE_2__* psz_uri; TYPE_2__* psz_name; int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_14__ {struct TYPE_14__* next; int /*<<< orphan*/  rc; } ;
typedef  TYPE_2__ input_item_owner_t ;
typedef  TYPE_2__ input_item_opaque_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,TYPE_2__**) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  info_category_Delete (TYPE_2__*) ; 
 int /*<<< orphan*/  input_item_slave_Delete (TYPE_2__*) ; 
 TYPE_2__* item_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_epg_Delete (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_event_manager_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void input_item_Release( input_item_t *p_item )
{
    input_item_owner_t *owner = item_owner(p_item);

    if( !vlc_atomic_rc_dec( &owner->rc ) )
        return;

    vlc_event_manager_fini( &p_item->event_manager );

    free( p_item->psz_name );
    free( p_item->psz_uri );
    free( p_item->p_stats );

    if( p_item->p_meta != NULL )
        vlc_meta_Delete( p_item->p_meta );

    for( input_item_opaque_t *o = p_item->opaques, *next; o != NULL; o = next )
    {
        next = o->next;
        free( o );
    }

    for( int i = 0; i < p_item->i_options; i++ )
        free( p_item->ppsz_options[i] );
    TAB_CLEAN( p_item->i_options, p_item->ppsz_options );
    free( p_item->optflagv );

    for( int i = 0; i < p_item->i_es; i++ )
    {
        es_format_Clean( p_item->es[i] );
        free( p_item->es[i] );
    }
    TAB_CLEAN( p_item->i_es, p_item->es );

    for( int i = 0; i < p_item->i_epg; i++ )
        vlc_epg_Delete( p_item->pp_epg[i] );
    TAB_CLEAN( p_item->i_epg, p_item->pp_epg );

    for( int i = 0; i < p_item->i_categories; i++ )
        info_category_Delete( p_item->pp_categories[i] );
    TAB_CLEAN( p_item->i_categories, p_item->pp_categories );

    for( int i = 0; i < p_item->i_slaves; i++ )
        input_item_slave_Delete( p_item->pp_slaves[i] );
    TAB_CLEAN( p_item->i_slaves, p_item->pp_slaves );

    vlc_mutex_destroy( &p_item->lock );
    free( owner );
}