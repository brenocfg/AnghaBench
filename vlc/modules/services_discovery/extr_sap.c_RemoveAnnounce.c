#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_10__ {int /*<<< orphan*/  pp_announces; int /*<<< orphan*/  i_announces; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/ * p_item; int /*<<< orphan*/ * p_sdp; } ;
typedef  TYPE_3__ sap_announce_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeSDP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  services_discovery_RemoveItem (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int RemoveAnnounce( services_discovery_t *p_sd,
                           sap_announce_t *p_announce )
{
    if( p_announce->p_sdp )
    {
        FreeSDP( p_announce->p_sdp );
        p_announce->p_sdp = NULL;
    }

    if( p_announce->p_item )
    {
        services_discovery_RemoveItem( p_sd, p_announce->p_item );
        input_item_Release( p_announce->p_item );
        p_announce->p_item = NULL;
    }

    services_discovery_sys_t *p_sys = p_sd->p_sys;
    TAB_REMOVE(p_sys->i_announces, p_sys->pp_announces, p_announce);
    free( p_announce );

    return VLC_SUCCESS;
}