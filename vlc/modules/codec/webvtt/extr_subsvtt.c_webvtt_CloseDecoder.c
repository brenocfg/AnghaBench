#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  webvtt_dom_node_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_css_rules; scalar_t__ p_root; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_css_rules_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  webvtt_domnode_ChainDelete (int /*<<< orphan*/ *) ; 

void webvtt_CloseDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;

    webvtt_domnode_ChainDelete( (webvtt_dom_node_t *) p_sys->p_root );

#ifdef HAVE_CSS
    vlc_css_rules_Delete( p_sys->p_css_rules );
#endif

    free( p_sys );
}