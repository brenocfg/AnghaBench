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
struct TYPE_4__ {int /*<<< orphan*/  i_style_flags; int /*<<< orphan*/  i_features; void* psz_monofontname; void* psz_fontname; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  MERGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MERGE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STYLE_HAS_BACKGROUND_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_BACKGROUND_COLOR ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_COLOR ; 
 int /*<<< orphan*/  STYLE_HAS_OUTLINE_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_OUTLINE_COLOR ; 
 int /*<<< orphan*/  STYLE_HAS_SHADOW_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_SHADOW_COLOR ; 
 int /*<<< orphan*/  STYLE_HAS_WRAP_INFO ; 
 int /*<<< orphan*/  STYLE_NO_DEFAULTS ; 
 int /*<<< orphan*/  e_wrapinfo ; 
 int /*<<< orphan*/  f_font_relsize ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  i_background_alpha ; 
 int /*<<< orphan*/  i_background_color ; 
 int /*<<< orphan*/  i_font_alpha ; 
 int /*<<< orphan*/  i_font_color ; 
 int /*<<< orphan*/  i_font_size ; 
 int /*<<< orphan*/  i_outline_alpha ; 
 int /*<<< orphan*/  i_outline_color ; 
 int /*<<< orphan*/  i_outline_width ; 
 int /*<<< orphan*/  i_shadow_alpha ; 
 int /*<<< orphan*/  i_shadow_color ; 
 int /*<<< orphan*/  i_shadow_width ; 
 int /*<<< orphan*/  i_spacing ; 
 void* strdup (void*) ; 

void text_style_Merge( text_style_t *p_dst, const text_style_t *p_src, bool b_override )
{
    if( p_src->psz_fontname && (!p_dst->psz_fontname || b_override) )
    {
        free( p_dst->psz_fontname );
        p_dst->psz_fontname = strdup( p_src->psz_fontname );
    }

    if( p_src->psz_monofontname && (!p_dst->psz_monofontname || b_override) )
    {
        free( p_dst->psz_monofontname );
        p_dst->psz_monofontname = strdup( p_src->psz_monofontname );
    }

    if( p_src->i_features != STYLE_NO_DEFAULTS )
    {
        MERGE(i_font_color,         STYLE_HAS_FONT_COLOR);
        MERGE(i_font_alpha,         STYLE_HAS_FONT_ALPHA);
        MERGE(i_outline_color,      STYLE_HAS_OUTLINE_COLOR);
        MERGE(i_outline_alpha,      STYLE_HAS_OUTLINE_ALPHA);
        MERGE(i_shadow_color,       STYLE_HAS_SHADOW_COLOR);
        MERGE(i_shadow_alpha,       STYLE_HAS_SHADOW_ALPHA);
        MERGE(i_background_color,   STYLE_HAS_BACKGROUND_COLOR);
        MERGE(i_background_alpha,   STYLE_HAS_BACKGROUND_ALPHA);
        MERGE(e_wrapinfo,            STYLE_HAS_WRAP_INFO);
        p_dst->i_features |= p_src->i_features;
        p_dst->i_style_flags |= p_src->i_style_flags;
    }

    MERGE_SIZE(f_font_relsize);
    MERGE_SIZE(i_font_size);
    MERGE_SIZE(i_outline_width);
    MERGE_SIZE(i_shadow_width);
    MERGE_SIZE(i_spacing);
}