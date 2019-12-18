#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_start; } ;
typedef  TYPE_1__ webvtt_dom_tag_t ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* p_parent; } ;
typedef  TYPE_2__ webvtt_dom_node_t ;
struct TYPE_7__ {int i_stop; int i_start; } ;
typedef  TYPE_3__ webvtt_dom_cue_t ;
typedef  int vlc_tick_t ;

/* Variables and functions */
 scalar_t__ NODE_CUE ; 
 scalar_t__ NODE_TAG ; 
 int VLC_TICK_INVALID ; 

__attribute__((used)) static vlc_tick_t webvtt_domnode_GetPlaybackTime( const webvtt_dom_node_t *p_node, bool b_end )
{
    for( ; p_node; p_node = p_node->p_parent )
    {
        if( p_node->type == NODE_TAG )
        {
            vlc_tick_t i_start = ((const webvtt_dom_tag_t *) p_node)->i_start;
            if( i_start > -1 && !b_end )
                return i_start;
        }
        else if( p_node->type == NODE_CUE )
        {
            break;
        }
    }
    if( p_node )
        return b_end ? ((const webvtt_dom_cue_t *) p_node)->i_stop:
                       ((const webvtt_dom_cue_t *) p_node)->i_start;
    return VLC_TICK_INVALID;
}