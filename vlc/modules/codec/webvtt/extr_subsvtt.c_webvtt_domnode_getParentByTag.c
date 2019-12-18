#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ psz_tag; } ;
typedef  TYPE_1__ webvtt_dom_tag_t ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* p_parent; } ;
typedef  TYPE_2__ webvtt_dom_node_t ;

/* Variables and functions */
 scalar_t__ NODE_TAG ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static webvtt_dom_node_t * webvtt_domnode_getParentByTag( webvtt_dom_node_t *p_parent,
                                                         const char *psz_tag )
{
    for( ; p_parent ; p_parent = p_parent->p_parent )
    {
        if( p_parent->type == NODE_TAG )
        {
            webvtt_dom_tag_t *p_node = (webvtt_dom_tag_t *) p_parent;
            if( p_node->psz_tag && psz_tag && !strcmp( p_node->psz_tag, psz_tag ) )
                break;
        }
    }
    return p_parent;
}