#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct entry_item {int /*<<< orphan*/  entry_item_list; int /*<<< orphan*/  p_item; scalar_t__ p_ns; } ;
struct TYPE_2__ {struct entry_item* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
typedef  struct entry_item services_discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct entry_item*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netbios_ns_destroy (scalar_t__) ; 
 int /*<<< orphan*/  netbios_ns_discover_stop (scalar_t__) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 struct entry_item* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

void bdsm_SdClose (vlc_object_t *p_this)
{
    services_discovery_t *sd = (services_discovery_t *)p_this;
    services_discovery_sys_t *p_sys = sd->p_sys;

    if( p_sys == NULL )
        return;

    if( p_sys->p_ns )
    {
        netbios_ns_discover_stop( p_sys->p_ns );
        netbios_ns_destroy( p_sys->p_ns );
    }

    for( size_t i = 0; i < vlc_array_count( &p_sys->entry_item_list ); i++ )
    {
        struct entry_item *p_entry_item;

        p_entry_item = vlc_array_item_at_index( &p_sys->entry_item_list, i );
        input_item_Release( p_entry_item->p_item );
        free( p_entry_item );
    }
    vlc_array_clear( &p_sys->entry_item_list );

    free( p_sys );
}