#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* p_next; } ;
typedef  TYPE_1__ webvtt_dom_node_t ;

/* Variables and functions */
 TYPE_1__* webvtt_domnode_getFirstChild (TYPE_1__*) ; 
 int /*<<< orphan*/  webvtt_domnode_setCSSStyle (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ webvtt_domnode_supportsCSSStyle (TYPE_1__*) ; 

__attribute__((used)) static void ClearCSSStyles( webvtt_dom_node_t *p_node )
{
    if( webvtt_domnode_supportsCSSStyle( p_node ) )
        webvtt_domnode_setCSSStyle( p_node, NULL );
    webvtt_dom_node_t *p_child = webvtt_domnode_getFirstChild( p_node );
    for ( ; p_child ; p_child = p_child->p_next )
        ClearCSSStyles( p_child );
}