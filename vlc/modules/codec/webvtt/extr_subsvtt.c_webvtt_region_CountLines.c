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
struct TYPE_5__ {TYPE_2__* p_child; } ;
typedef  TYPE_1__ webvtt_region_t ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ webvtt_dom_node_t ;
struct TYPE_7__ {scalar_t__ i_lines; } ;
typedef  TYPE_3__ webvtt_dom_cue_t ;

/* Variables and functions */
 scalar_t__ NODE_CUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static unsigned webvtt_region_CountLines( const webvtt_region_t *p_region )
{
    unsigned i_lines = 0;
    for( const webvtt_dom_node_t *p_node = p_region->p_child;
                                  p_node; p_node = p_node->p_next )
    {
        assert( p_node->type == NODE_CUE );
        if( p_node->type != NODE_CUE )
            continue;
        i_lines += ((const webvtt_dom_cue_t *)p_node)->i_lines;
    }
    return i_lines;
}