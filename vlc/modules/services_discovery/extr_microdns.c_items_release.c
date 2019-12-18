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
struct item {struct item* psz_uri; int /*<<< orphan*/ * p_renderer_item; int /*<<< orphan*/ * p_input_item; } ;
struct discovery_sys {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct item*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_renderer_item_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
items_release( struct discovery_sys *p_sys, struct item *p_item )
{
    (void) p_sys;
    if( p_item->p_input_item != NULL )
    {
        input_item_Release( p_item->p_input_item );
    }
    else
    {
        assert( p_item->p_renderer_item != NULL );
        vlc_renderer_item_release( p_item->p_renderer_item );
    }

    free( p_item->psz_uri );
    free( p_item );
}