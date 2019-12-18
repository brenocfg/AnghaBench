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
struct TYPE_4__ {int i_font_color; int i_outline_color; int i_shadow_color; int i_background_color; int i_outline_width; int i_spacing; int /*<<< orphan*/  e_wrapinfo; scalar_t__ i_shadow_width; void* i_background_alpha; void* i_shadow_alpha; void* i_outline_alpha; void* i_font_alpha; int /*<<< orphan*/  i_font_size; int /*<<< orphan*/  f_font_relsize; int /*<<< orphan*/  i_style_flags; int /*<<< orphan*/  i_features; int /*<<< orphan*/ * psz_monofontname; int /*<<< orphan*/ * psz_fontname; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 void* STYLE_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  STYLE_DEFAULT_FONT_SIZE ; 
 int /*<<< orphan*/  STYLE_DEFAULT_REL_FONT_SIZE ; 
 int /*<<< orphan*/  STYLE_FULLY_SET ; 
 int STYLE_NO_DEFAULTS ; 
 int /*<<< orphan*/  STYLE_OUTLINE ; 
 int /*<<< orphan*/  STYLE_WRAP_DEFAULT ; 
 TYPE_1__* calloc (int,int) ; 

text_style_t *text_style_Create( int i_defaults )
{
    text_style_t *p_style = calloc( 1, sizeof(*p_style) );
    if( !p_style )
        return NULL;

    if( i_defaults == STYLE_NO_DEFAULTS )
        return p_style;

    /* initialize to default text style (FIXME: by flag) */
    p_style->psz_fontname = NULL;
    p_style->psz_monofontname = NULL;
    p_style->i_features = STYLE_FULLY_SET;
    p_style->i_style_flags = STYLE_OUTLINE;
    p_style->f_font_relsize = STYLE_DEFAULT_REL_FONT_SIZE;
    p_style->i_font_size = STYLE_DEFAULT_FONT_SIZE;
    p_style->i_font_color = 0xffffff;
    p_style->i_font_alpha = STYLE_ALPHA_OPAQUE;
    p_style->i_outline_color = 0x000000;
    p_style->i_outline_alpha = STYLE_ALPHA_OPAQUE;
    p_style->i_shadow_color = 0x808080;
    p_style->i_shadow_alpha = STYLE_ALPHA_OPAQUE;
    p_style->i_background_color = 0x000000;
    p_style->i_background_alpha = STYLE_ALPHA_OPAQUE;
    p_style->i_outline_width = 1;
    p_style->i_shadow_width = 0;
    p_style->i_spacing = -1;
    p_style->e_wrapinfo = STYLE_WRAP_DEFAULT;

    return p_style;
}