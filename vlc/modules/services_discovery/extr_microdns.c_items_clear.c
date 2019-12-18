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
struct item {int dummy; } ;
struct discovery_sys {int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  items_release (struct discovery_sys*,struct item*) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 struct item* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
items_clear( struct discovery_sys *p_sys )
{
    for( size_t i = 0; i < vlc_array_count( &p_sys->items ); ++i )
    {
        struct item *p_item = vlc_array_item_at_index( &p_sys->items, i );
        items_release( p_sys, p_item );
    }
    vlc_array_clear( &p_sys->items );
}