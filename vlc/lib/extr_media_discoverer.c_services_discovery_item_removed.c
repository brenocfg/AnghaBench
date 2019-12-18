#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* sys; } ;
struct TYPE_9__ {TYPE_1__ owner; } ;
typedef  TYPE_2__ services_discovery_t ;
struct TYPE_10__ {int /*<<< orphan*/ * p_input_item; } ;
typedef  TYPE_3__ libvlc_media_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_mlist; } ;
typedef  TYPE_4__ libvlc_media_discoverer_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_internal_remove_index (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* libvlc_media_list_item_at_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libvlc_media_list_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_release (TYPE_3__*) ; 

__attribute__((used)) static void services_discovery_item_removed( services_discovery_t *sd,
                                             input_item_t *p_item )
{
    libvlc_media_t * p_md;
    libvlc_media_discoverer_t *p_mdis = sd->owner.sys;

    int i, count = libvlc_media_list_count( p_mdis->p_mlist );
    libvlc_media_list_lock( p_mdis->p_mlist );
    for( i = 0; i < count; i++ )
    {
        p_md = libvlc_media_list_item_at_index( p_mdis->p_mlist, i );
        assert(p_md != NULL);
        if( p_md->p_input_item == p_item )
        {
            libvlc_media_list_internal_remove_index( p_mdis->p_mlist, i );
            libvlc_media_release( p_md );
            break;
        }
        libvlc_media_release( p_md );
    }
    libvlc_media_list_unlock( p_mdis->p_mlist );
}