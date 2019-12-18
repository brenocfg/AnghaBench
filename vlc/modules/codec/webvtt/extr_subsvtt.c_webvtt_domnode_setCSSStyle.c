#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  webvtt_dom_node_t ;
typedef  int /*<<< orphan*/  text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** get_ppCSSStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void webvtt_domnode_setCSSStyle( webvtt_dom_node_t *p_node, text_style_t *p_style )
{
    text_style_t **pp_style = get_ppCSSStyle( p_node );
    if( !pp_style )
    {
        assert( pp_style );
        if( p_style )
            text_style_Delete( p_style );
        return;
    }
    if( *pp_style )
        text_style_Delete( *pp_style );
    *pp_style = p_style;
}