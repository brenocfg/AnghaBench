#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  webvtt_region_t ;
typedef  int /*<<< orphan*/  webvtt_dom_text_t ;
typedef  int /*<<< orphan*/  webvtt_dom_tag_t ;
struct TYPE_3__ {scalar_t__ type; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ webvtt_dom_node_t ;
typedef  int /*<<< orphan*/  webvtt_dom_cue_t ;

/* Variables and functions */
 scalar_t__ NODE_CUE ; 
 scalar_t__ NODE_REGION ; 
 scalar_t__ NODE_TAG ; 
 scalar_t__ NODE_TEXT ; 
 int /*<<< orphan*/  webvtt_dom_cue_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webvtt_dom_tag_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webvtt_dom_text_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webvtt_region_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void webvtt_domnode_ChainDelete( webvtt_dom_node_t *p_node )
{
    while( p_node )
    {
        webvtt_dom_node_t *p_next = p_node->p_next;

        if( p_node->type == NODE_TAG )
            webvtt_dom_tag_Delete( (webvtt_dom_tag_t *) p_node );
        else if( p_node->type == NODE_TEXT )
            webvtt_dom_text_Delete( (webvtt_dom_text_t *) p_node );
        else if( p_node->type == NODE_CUE )
            webvtt_dom_cue_Delete( (webvtt_dom_cue_t *) p_node );
        else if( p_node->type == NODE_REGION )
            webvtt_region_Delete( (webvtt_region_t *) p_node );

        p_node = p_next;
    }
}