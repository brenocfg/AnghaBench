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
struct TYPE_3__ {scalar_t__ i_lines; int /*<<< orphan*/ * p_child; } ;
typedef  TYPE_1__ webvtt_dom_cue_t ;

/* Variables and functions */
 int /*<<< orphan*/  webvtt_domnode_ChainDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void webvtt_dom_cue_ClearText( webvtt_dom_cue_t *p_cue )
{
    webvtt_domnode_ChainDelete( p_cue->p_child );
    p_cue->p_child = NULL;
    p_cue->i_lines = 0;
}