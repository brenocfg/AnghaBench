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
struct TYPE_4__ {int /*<<< orphan*/  settings; int /*<<< orphan*/ * p_cssstyle; scalar_t__ i_lines; int /*<<< orphan*/ * p_child; void* i_stop; void* i_start; int /*<<< orphan*/ * psz_id; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ webvtt_dom_cue_t ;
typedef  void* vlc_tick_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_CUE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  webvtt_cue_settings_Init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static webvtt_dom_cue_t * webvtt_dom_cue_New( vlc_tick_t i_start, vlc_tick_t i_end )
{
    webvtt_dom_cue_t *p_cue = calloc( 1, sizeof(*p_cue) );
    if( p_cue )
    {
        p_cue->type = NODE_CUE;
        p_cue->psz_id = NULL;
        p_cue->i_start = i_start;
        p_cue->i_stop = i_end;
        p_cue->p_child = NULL;
        p_cue->i_lines = 0;
        p_cue->p_cssstyle = NULL;
        webvtt_cue_settings_Init( &p_cue->settings );
    }
    return p_cue;
}