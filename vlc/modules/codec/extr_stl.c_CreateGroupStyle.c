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
struct TYPE_4__ {int i_features; int i_background_color; int /*<<< orphan*/  f_font_relsize; scalar_t__ i_font_size; int /*<<< orphan*/  i_background_alpha; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  STYLE_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  STYLE_DEFAULT_REL_FONT_SIZE ; 
 int STYLE_HAS_BACKGROUND_ALPHA ; 
 int STYLE_HAS_BACKGROUND_COLOR ; 
 int STYLE_HAS_FLAGS ; 
 int /*<<< orphan*/  STYLE_NO_DEFAULTS ; 
 TYPE_1__* text_style_Create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static text_style_t * CreateGroupStyle()
{
    text_style_t *p_style = text_style_Create(STYLE_NO_DEFAULTS);
    if(p_style)
    {
        p_style->i_features = STYLE_HAS_FLAGS|STYLE_HAS_BACKGROUND_ALPHA|STYLE_HAS_BACKGROUND_COLOR;
        /* Teletext needs default background to black */
        p_style->i_background_alpha = STYLE_ALPHA_OPAQUE;
        p_style->i_background_color = 0x000000;
        p_style->i_font_size = 0;
        p_style->f_font_relsize = STYLE_DEFAULT_REL_FONT_SIZE;
    }
    return p_style;
}