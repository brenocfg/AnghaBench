#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_child; struct TYPE_4__* psz_tag; struct TYPE_4__* psz_attrs; int /*<<< orphan*/  p_cssstyle; } ;
typedef  TYPE_1__ webvtt_dom_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  webvtt_domnode_ChainDelete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void webvtt_dom_tag_Delete( webvtt_dom_tag_t *p_node )
{
    text_style_Delete( p_node->p_cssstyle );
    free( p_node->psz_attrs );
    free( p_node->psz_tag );
    webvtt_domnode_ChainDelete( p_node->p_child );
    free( p_node );
}