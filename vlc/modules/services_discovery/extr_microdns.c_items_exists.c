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
struct item {int /*<<< orphan*/  i_last_seen; int /*<<< orphan*/  psz_uri; } ;
struct discovery_sys {int /*<<< orphan*/  items; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 struct item* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static bool
items_exists( struct discovery_sys *p_sys, const char *psz_uri )
{
    for( size_t i = 0; i < vlc_array_count( &p_sys->items ); ++i )
    {
        struct item *p_item = vlc_array_item_at_index( &p_sys->items, i );
        if( strcmp( p_item->psz_uri, psz_uri ) == 0 )
        {
            p_item->i_last_seen = vlc_tick_now();
            return true;
        }
    }
    return false;
}