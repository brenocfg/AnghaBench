#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double value; int b_auto; } ;
struct TYPE_5__ {int b_auto; double value; } ;
struct TYPE_7__ {int b_snap_to_lines; int position; int /*<<< orphan*/  align; TYPE_2__ size; void* positionalign; int /*<<< orphan*/  linealign; TYPE_1__ line; void* vertical; int /*<<< orphan*/ * psz_region; } ;
typedef  TYPE_3__ webvtt_cue_settings_t ;

/* Variables and functions */
 void* WEBVTT_ALIGN_AUTO ; 
 int /*<<< orphan*/  WEBVTT_ALIGN_CENTER ; 
 int /*<<< orphan*/  WEBVTT_ALIGN_START ; 

__attribute__((used)) static void webvtt_cue_settings_Init( webvtt_cue_settings_t *p_settings )
{
    p_settings->psz_region = NULL;
    p_settings->vertical = WEBVTT_ALIGN_AUTO;
    p_settings->b_snap_to_lines = true;
    p_settings->line.b_auto = true;
    p_settings->line.value = 1.0;
    p_settings->linealign = WEBVTT_ALIGN_START;
    p_settings->position = -1;
    p_settings->positionalign = WEBVTT_ALIGN_AUTO;
    p_settings->size.value = 1.0; /* 100% */
    p_settings->size.b_auto = true;
    p_settings->align = WEBVTT_ALIGN_CENTER;
}