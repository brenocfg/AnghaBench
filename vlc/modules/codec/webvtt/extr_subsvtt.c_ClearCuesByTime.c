#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_child; } ;
typedef  TYPE_1__ webvtt_region_t ;
struct TYPE_7__ {scalar_t__ type; struct TYPE_7__* p_next; } ;
typedef  TYPE_2__ webvtt_dom_node_t ;
struct TYPE_8__ {scalar_t__ i_stop; } ;
typedef  TYPE_3__ webvtt_dom_cue_t ;
typedef  scalar_t__ vlc_tick_t ;

/* Variables and functions */
 scalar_t__ NODE_CUE ; 
 scalar_t__ NODE_REGION ; 
 int /*<<< orphan*/  webvtt_dom_cue_Delete (TYPE_3__*) ; 

__attribute__((used)) static void ClearCuesByTime( webvtt_dom_node_t **pp_next, vlc_tick_t i_time )
{
    while( *pp_next )
    {
        webvtt_dom_node_t *p_node = *pp_next;
        if( p_node )
        {
            if( p_node->type == NODE_CUE )
            {
                webvtt_dom_cue_t *p_cue = (webvtt_dom_cue_t *)p_node;
                if( p_cue->i_stop <= i_time )
                {
                    *pp_next = p_node->p_next;
                    p_node->p_next = NULL;
                    webvtt_dom_cue_Delete( p_cue );
                    continue;
                }
            }
            else if( p_node->type == NODE_REGION )
            {
                webvtt_region_t *p_region = (webvtt_region_t *) p_node;
                ClearCuesByTime( &p_region->p_child, i_time );
            }
            pp_next = &p_node->p_next;
        }
    }
}