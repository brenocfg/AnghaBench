#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_3__* p_style; } ;
typedef  TYPE_1__ stl_sg_t ;
struct TYPE_5__ {int i_style_flags; int f_font_relsize; int i_background_color; int i_font_color; int /*<<< orphan*/  i_features; } ;

/* Variables and functions */
 TYPE_3__* CreateGroupStyle () ; 
 int STYLE_BACKGROUND ; 
 int STYLE_DEFAULT_REL_FONT_SIZE ; 
 int STYLE_DOUBLEWIDTH ; 
 int STYLE_HALFWIDTH ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_COLOR ; 

__attribute__((used)) static void GroupParseTeletext(stl_sg_t *p_group, uint8_t code)
{
    if(p_group->p_style == NULL &&
      !(p_group->p_style = CreateGroupStyle()))
        return;

    /* See ETS 300 706 Table 26 as EBU 3264 does only name values
       and does not explain at all */

    static const uint32_t colors[] =
    {
        0x000000,
        0xFF0000,
        0x00FF00,
        0xFFFF00,
        0x0000FF,
        0xFF00FF,
        0x00FFFF,
        0xFFFFFF,
    };

    /* Teletext data received, so we need to enable background */
    p_group->p_style->i_style_flags |= STYLE_BACKGROUND;

    switch(code)
    {
        case 0x0c:
            p_group->p_style->f_font_relsize = STYLE_DEFAULT_REL_FONT_SIZE;
            p_group->p_style->i_style_flags &= ~(STYLE_DOUBLEWIDTH|STYLE_HALFWIDTH);
            break;

        case 0x0d: /* double height */
            p_group->p_style->f_font_relsize = STYLE_DEFAULT_REL_FONT_SIZE * 2;
            p_group->p_style->i_style_flags &= ~STYLE_DOUBLEWIDTH;
            p_group->p_style->i_style_flags |= STYLE_HALFWIDTH;
            break;

        case 0x0e: /* double width */
            p_group->p_style->f_font_relsize = STYLE_DEFAULT_REL_FONT_SIZE;
            p_group->p_style->i_style_flags &= ~STYLE_HALFWIDTH;
            p_group->p_style->i_style_flags |= STYLE_DOUBLEWIDTH;
            break;

        case 0x0f: /* double size */
            p_group->p_style->f_font_relsize = STYLE_DEFAULT_REL_FONT_SIZE * 2;
            p_group->p_style->i_style_flags &= ~(STYLE_DOUBLEWIDTH|STYLE_HALFWIDTH);
            break;

        case 0x1d:
            p_group->p_style->i_background_color = p_group->p_style->i_font_color;
            p_group->p_style->i_features &= ~STYLE_HAS_FONT_COLOR;
            break;

        case 0x1c:
            p_group->p_style->i_background_color = colors[0];
            break;

        default:
            if(code < 8)
            {
                p_group->p_style->i_font_color = colors[code];
                p_group->p_style->i_features |= STYLE_HAS_FONT_COLOR;
            }

            /* Need to handle Mosaic ? Really ? */
            break;
    }

}