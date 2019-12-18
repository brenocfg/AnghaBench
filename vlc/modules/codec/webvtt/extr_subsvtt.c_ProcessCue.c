#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* p_parent; struct TYPE_6__* p_next; } ;
typedef  TYPE_1__ webvtt_dom_node_t ;
struct TYPE_7__ {TYPE_1__* p_child; int /*<<< orphan*/  i_lines; } ;
typedef  TYPE_2__ webvtt_dom_cue_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 TYPE_1__* CreateDomNodes (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webvtt_domnode_Debug (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ProcessCue( decoder_t *p_dec, const char *psz, webvtt_dom_cue_t *p_cue )
{
    VLC_UNUSED(p_dec);

    if( p_cue->p_child )
        return;
    p_cue->p_child = CreateDomNodes( psz, &p_cue->i_lines );
    for( webvtt_dom_node_t *p_child = p_cue->p_child; p_child; p_child = p_child->p_next )
        p_child->p_parent = (webvtt_dom_node_t *)p_cue;
#ifdef SUBSVTT_DEBUG
    webvtt_domnode_Debug( (webvtt_dom_node_t *) p_cue, 0 );
#endif
}