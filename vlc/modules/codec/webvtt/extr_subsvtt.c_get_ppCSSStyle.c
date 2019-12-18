#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * p_cssstyle; } ;
typedef  TYPE_1__ webvtt_region_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_cssstyle; } ;
typedef  TYPE_2__ webvtt_dom_tag_t ;
struct TYPE_8__ {int type; } ;
typedef  TYPE_3__ webvtt_dom_node_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p_cssstyle; } ;
typedef  TYPE_4__ webvtt_dom_cue_t ;
typedef  int /*<<< orphan*/  text_style_t ;

/* Variables and functions */
#define  NODE_CUE 130 
#define  NODE_REGION 129 
#define  NODE_TAG 128 

__attribute__((used)) static text_style_t ** get_ppCSSStyle( webvtt_dom_node_t *p_node )
{
    switch( p_node->type )
    {
        case NODE_CUE:
            return &((webvtt_dom_cue_t *)p_node)->p_cssstyle;
        case NODE_REGION:
            return &((webvtt_region_t *)p_node)->p_cssstyle;
        case NODE_TAG:
            return &((webvtt_dom_tag_t *)p_node)->p_cssstyle;
        default:
            return NULL;
    }
}