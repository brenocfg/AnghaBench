#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_child; } ;
typedef  TYPE_1__ webvtt_region_t ;
struct TYPE_8__ {TYPE_3__* p_child; } ;
typedef  TYPE_2__ webvtt_dom_tag_t ;
struct TYPE_9__ {int type; } ;
typedef  TYPE_3__ webvtt_dom_node_t ;
struct TYPE_10__ {TYPE_3__* p_child; } ;
typedef  TYPE_4__ webvtt_dom_cue_t ;

/* Variables and functions */
#define  NODE_CUE 130 
#define  NODE_REGION 129 
#define  NODE_TAG 128 

__attribute__((used)) static webvtt_dom_node_t * webvtt_domnode_getFirstChild( webvtt_dom_node_t *p_node )
{
    webvtt_dom_node_t *p_child = NULL;
    switch( p_node->type )
    {
        case NODE_CUE:
            p_child  = ((webvtt_dom_cue_t *)p_node)->p_child;
            break;
        case NODE_REGION:
            p_child  = ((webvtt_region_t *)p_node)->p_child;
            break;
        case NODE_TAG:
            p_child  = ((webvtt_dom_tag_t *)p_node)->p_child;
            break;
        default:
            break;
    }
    return p_child;
}