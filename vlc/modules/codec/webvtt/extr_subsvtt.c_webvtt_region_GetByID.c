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
struct TYPE_8__ {scalar_t__ psz_id; } ;
typedef  TYPE_2__ webvtt_region_t ;
struct TYPE_9__ {scalar_t__ type; struct TYPE_9__* p_next; } ;
typedef  TYPE_3__ webvtt_dom_node_t ;
struct TYPE_10__ {TYPE_1__* p_root; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_7__ {TYPE_3__* p_child; } ;

/* Variables and functions */
 scalar_t__ NODE_REGION ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static webvtt_region_t * webvtt_region_GetByID( decoder_sys_t *p_sys,
                                                const char *psz_id )
{
    if( !psz_id )
        return NULL;
    for( webvtt_dom_node_t *p_node = p_sys->p_root->p_child;
                            p_node; p_node = p_node->p_next )
    {
        if( p_node->type == NODE_REGION )
        {
            webvtt_region_t *p_region = (webvtt_region_t *) p_node;
            if( p_region->psz_id && !strcmp( psz_id, p_region->psz_id ) )
                return p_region;
        }
    }
    return NULL;
}