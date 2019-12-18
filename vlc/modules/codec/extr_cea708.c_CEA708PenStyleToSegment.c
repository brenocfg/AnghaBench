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
struct TYPE_9__ {int i_features; int /*<<< orphan*/  f_font_relsize; int /*<<< orphan*/  i_style_flags; void* i_font_alpha; void* i_font_color; void* i_background_color; void* i_background_alpha; } ;
typedef  TYPE_3__ text_style_t ;
struct TYPE_8__ {scalar_t__ opacity; int /*<<< orphan*/  color; } ;
struct TYPE_7__ {scalar_t__ opacity; int /*<<< orphan*/  color; } ;
struct TYPE_10__ {int font; int size; scalar_t__ b_underline; scalar_t__ b_italics; TYPE_2__ foreground; TYPE_1__ background; } ;
typedef  TYPE_4__ cea708_pen_style_t ;

/* Variables and functions */
 void* CEA708AlphaConvert (scalar_t__) ; 
 void* CEA708ColorConvert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CEA708_FONTRELSIZE_LARGE ; 
 int /*<<< orphan*/  CEA708_FONTRELSIZE_SMALL ; 
 int /*<<< orphan*/  CEA708_FONTRELSIZE_STANDARD ; 
#define  CEA708_FONT_CASUAL 137 
#define  CEA708_FONT_CURSIVE 136 
#define  CEA708_FONT_MONOSPACED 135 
#define  CEA708_FONT_MONO_SANS_SERIF 134 
#define  CEA708_FONT_PROP 133 
#define  CEA708_FONT_PROP_SANS_SERIF 132 
#define  CEA708_FONT_SMALL_CAPS 131 
#define  CEA708_FONT_UNDEFINED 130 
 scalar_t__ CEA708_OPACITY_FLASH ; 
 scalar_t__ CEA708_OPACITY_TRANSPARENT ; 
#define  CEA708_PEN_SIZE_LARGE 129 
#define  CEA708_PEN_SIZE_SMALL 128 
 int /*<<< orphan*/  STYLE_BACKGROUND ; 
 int /*<<< orphan*/  STYLE_BLINK_BACKGROUND ; 
 int /*<<< orphan*/  STYLE_BLINK_FOREGROUND ; 
 int STYLE_HAS_BACKGROUND_ALPHA ; 
 int STYLE_HAS_BACKGROUND_COLOR ; 
 int STYLE_HAS_FONT_ALPHA ; 
 int STYLE_HAS_FONT_COLOR ; 
 int /*<<< orphan*/  STYLE_ITALIC ; 
 int /*<<< orphan*/  STYLE_MONOSPACED ; 
 int /*<<< orphan*/  STYLE_UNDERLINE ; 

__attribute__((used)) static void CEA708PenStyleToSegment( const cea708_pen_style_t *ps, text_style_t *s )
{
    if( ps->background.opacity != CEA708_OPACITY_TRANSPARENT )
    {
        s->i_background_alpha = CEA708AlphaConvert( ps->background.opacity );
        s->i_style_flags |= STYLE_BACKGROUND;
        s->i_background_color = CEA708ColorConvert( ps->background.color );
        s->i_features |= STYLE_HAS_BACKGROUND_COLOR|STYLE_HAS_BACKGROUND_ALPHA;
        if( ps->background.opacity == CEA708_OPACITY_FLASH )
            s->i_style_flags |= STYLE_BLINK_BACKGROUND;
    }
    s->i_font_color = CEA708ColorConvert( ps->foreground.color );
    s->i_font_alpha = CEA708AlphaConvert( ps->foreground.opacity );
    s->i_features |= STYLE_HAS_FONT_ALPHA|STYLE_HAS_FONT_COLOR;
    if( ps->foreground.opacity == CEA708_OPACITY_FLASH )
        s->i_style_flags |= STYLE_BLINK_FOREGROUND;

    if( ps->b_italics )
        s->i_style_flags |= STYLE_ITALIC;
    if( ps->b_underline )
        s->i_style_flags |= STYLE_UNDERLINE;

    switch( ps->font )
    {
        default:
        case CEA708_FONT_UNDEFINED:
        case CEA708_FONT_MONOSPACED:
        case CEA708_FONT_MONO_SANS_SERIF:
            s->i_style_flags |= STYLE_MONOSPACED;
            break;
        case CEA708_FONT_PROP:
        case CEA708_FONT_PROP_SANS_SERIF:
        case CEA708_FONT_CASUAL:
        case CEA708_FONT_CURSIVE:
        case CEA708_FONT_SMALL_CAPS:
            break;
    }

    switch( ps->size )
    {
        case CEA708_PEN_SIZE_SMALL:
            s->f_font_relsize = CEA708_FONTRELSIZE_SMALL;
            break;
        case CEA708_PEN_SIZE_LARGE:
            s->f_font_relsize = CEA708_FONTRELSIZE_LARGE;
            break;
        default:
            s->f_font_relsize = CEA708_FONTRELSIZE_STANDARD;
            break;
    }
}