#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float y; float w; float x; float h; } ;
typedef  TYPE_3__ webvtt_rect_t ;
struct TYPE_8__ {float value; int /*<<< orphan*/  b_auto; } ;
struct TYPE_7__ {float value; int /*<<< orphan*/  b_auto; } ;
struct TYPE_10__ {float position; scalar_t__ align; scalar_t__ positionalign; scalar_t__ vertical; TYPE_2__ size; TYPE_1__ line; scalar_t__ b_snap_to_lines; } ;
typedef  TYPE_4__ webvtt_cue_settings_t ;
typedef  enum webvtt_align_e { ____Placeholder_webvtt_align_e } webvtt_align_e ;

/* Variables and functions */
 scalar_t__ WEBVTT_ALIGN_AUTO ; 
 int WEBVTT_ALIGN_CENTER ; 
 scalar_t__ WEBVTT_ALIGN_LEFT ; 
 scalar_t__ WEBVTT_ALIGN_RIGHT ; 
 int WEBVTT_ALIGN_START ; 
 float WEBVTT_LINE_TO_HEIGHT_RATIO ; 
 float WEBVTT_REGION_LINES_COUNT ; 

__attribute__((used)) static void webvtt_get_cueboxrect( const webvtt_cue_settings_t *p_settings,
                                   webvtt_rect_t *p_rect )
{
    float extent;
    float indent_anchor_position;
    enum webvtt_align_e alignment_on_indent_anchor;

    /* Position of top or left depending on writing direction */
    float line_offset;
    if( !p_settings->line.b_auto ) /* numerical */
    {
        if( p_settings->b_snap_to_lines ) /* line # */
            line_offset = p_settings->line.value /
                          (WEBVTT_REGION_LINES_COUNT * WEBVTT_LINE_TO_HEIGHT_RATIO);
        else
            line_offset = p_settings->line.value;
    }
    else line_offset = 1.0;

    if( p_settings->position < 0 )
    {
        if( p_settings->align == WEBVTT_ALIGN_LEFT )
            indent_anchor_position = 0;
        else if( p_settings->align == WEBVTT_ALIGN_RIGHT )
            indent_anchor_position = 1.0;
        else
            indent_anchor_position = 0.5; /* center */
    }
    else indent_anchor_position = p_settings->position;

    if( p_settings->positionalign == WEBVTT_ALIGN_AUTO )
    {
        /* text align */
        if( p_settings->align == WEBVTT_ALIGN_LEFT ||
            p_settings->align == WEBVTT_ALIGN_RIGHT )
            alignment_on_indent_anchor = p_settings->align;
        else
            alignment_on_indent_anchor = WEBVTT_ALIGN_CENTER;
    }
    else alignment_on_indent_anchor = p_settings->positionalign;

    if( !p_settings->size.b_auto )
        extent = p_settings->size.value;
    else
        extent = 0.0;

    /* apply */

    /* we need 100% or size for inner_align to work on writing direction */
    if( p_settings->vertical == WEBVTT_ALIGN_AUTO ) /* Horizontal text */
    {
        p_rect->y = line_offset > 0 ? line_offset : 1.0 + line_offset;
        p_rect->w = (extent) ? extent : 1.0;
        if( indent_anchor_position > 0 &&
            (alignment_on_indent_anchor == WEBVTT_ALIGN_LEFT ||
             alignment_on_indent_anchor == WEBVTT_ALIGN_START) )
        {
            p_rect->x  = indent_anchor_position;
            p_rect->w -= p_rect->x;
        }
    }
    else /* Vertical text */
    {
        if( p_settings->vertical == WEBVTT_ALIGN_LEFT )
            p_rect->x = line_offset > 0 ? 1.0 - line_offset : -line_offset;
        else
            p_rect->x = line_offset > 0 ? line_offset : 1.0 + line_offset;
        p_rect->y = (extent) ? extent : 1.0;

        if( indent_anchor_position > 0 &&
            alignment_on_indent_anchor == WEBVTT_ALIGN_START )
        {
            p_rect->y  = indent_anchor_position;
            p_rect->h -= p_rect->y;
        }
    }
}