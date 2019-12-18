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
struct TYPE_4__ {int align; int const vertical; } ;
struct TYPE_5__ {TYPE_1__ settings; } ;
typedef  TYPE_2__ webvtt_dom_cue_t ;

/* Variables and functions */
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_RIGHT ; 
#define  WEBVTT_ALIGN_END 131 
#define  WEBVTT_ALIGN_LEFT 130 
#define  WEBVTT_ALIGN_RIGHT 129 
#define  WEBVTT_ALIGN_START 128 

__attribute__((used)) static int GetCueTextAlignment( const webvtt_dom_cue_t *p_cue )
{
    switch( p_cue->settings.align )
    {
        case WEBVTT_ALIGN_LEFT:
            return SUBPICTURE_ALIGN_LEFT;
        case WEBVTT_ALIGN_RIGHT:
            return SUBPICTURE_ALIGN_RIGHT;
        case WEBVTT_ALIGN_START: /* vertical provides rl or rl base direction */
            return (p_cue->settings.vertical == WEBVTT_ALIGN_RIGHT) ?
                     SUBPICTURE_ALIGN_RIGHT : SUBPICTURE_ALIGN_LEFT;
        case WEBVTT_ALIGN_END:
            return (p_cue->settings.vertical == WEBVTT_ALIGN_RIGHT) ?
                     SUBPICTURE_ALIGN_LEFT : SUBPICTURE_ALIGN_RIGHT;
        default:
            return 0;
    }
}