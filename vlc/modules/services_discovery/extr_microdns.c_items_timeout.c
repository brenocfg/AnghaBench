#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_renderer_discovery_t ;
struct item {scalar_t__ i_last_seen; int /*<<< orphan*/  p_renderer_item; int /*<<< orphan*/  p_input_item; } ;
struct discovery_sys {int /*<<< orphan*/  items; } ;
typedef  int /*<<< orphan*/  services_discovery_t ;

/* Variables and functions */
 scalar_t__ TIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  items_release (struct discovery_sys*,struct item*) ; 
 int /*<<< orphan*/  services_discovery_RemoveItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 struct item* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_rd_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void
items_timeout( struct discovery_sys *p_sys, services_discovery_t *p_sd,
               vlc_renderer_discovery_t *p_rd )
{
    assert( p_rd != NULL || p_sd != NULL );
    vlc_tick_t i_now = vlc_tick_now();

    /* Remove items that are not seen since TIMEOUT */
    for( size_t i = 0; i < vlc_array_count( &p_sys->items ); ++i )
    {
        struct item *p_item = vlc_array_item_at_index( &p_sys->items, i );
        if( i_now - p_item->i_last_seen > TIMEOUT )
        {
            if( p_sd != NULL )
                services_discovery_RemoveItem( p_sd, p_item->p_input_item );
            else
                vlc_rd_remove_item( p_rd, p_item->p_renderer_item );
            items_release( p_sys, p_item );
            vlc_array_remove( &p_sys->items, i-- );
        }
    }
}