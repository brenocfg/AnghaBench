#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ i_chroma; unsigned int i_height; unsigned int i_width; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_12__ {unsigned int columns; int* color_map; TYPE_1__* text; } ;
typedef  TYPE_4__ vbi_page ;
typedef  int vbi_opacity ;
typedef  int uint32_t ;
struct TYPE_13__ {TYPE_2__* p; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_10__ {unsigned int i_pitch; int /*<<< orphan*/ * p_pixels; } ;
struct TYPE_9__ {int opacity; int background; } ;

/* Variables and functions */
#define  VBI_OPAQUE 131 
#define  VBI_SEMI_TRANSPARENT 130 
#define  VBI_TRANSPARENT_FULL 129 
#define  VBI_TRANSPARENT_SPACE 128 
 scalar_t__ VLC_CODEC_RGBA ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int OpaquePage( picture_t *p_src, const vbi_page *p_page,
                       const video_format_t *p_fmt, bool b_opaque, const int text_offset )
{
    unsigned int    x, y;

    assert( p_fmt->i_chroma == VLC_CODEC_RGBA );

    /* Kludge since zvbi doesn't provide an option to specify opacity. */
    for( y = 0; y < p_fmt->i_height; y++ )
    {
        for( x = 0; x < p_fmt->i_width; x++ )
        {
            const vbi_opacity opacity = p_page->text[ text_offset + y/10 * p_page->columns + x/12 ].opacity;
            const int background = p_page->text[ text_offset + y/10 * p_page->columns + x/12 ].background;
            uint32_t *p_pixel = (uint32_t*)&p_src->p->p_pixels[y * p_src->p->i_pitch + 4*x];

            switch( opacity )
            {
            /* Display foreground and background color */
            /* To make the boxed text "closed captioning" transparent
             * change true to false.
             */
            case VBI_OPAQUE:
            /* alpha blend video into background color */
            case VBI_SEMI_TRANSPARENT:
                if( b_opaque )
                    break;
                /* fallthrough */
            /* Full text transparency. only foreground color is show */
            case VBI_TRANSPARENT_FULL:
                if( (*p_pixel) != (0xff000000 | p_page->color_map[background] ) )
                    break;
                /* fallthrough */
            /* Show video instead of this character */
            case VBI_TRANSPARENT_SPACE:
                *p_pixel = 0;
                break;
            }
        }
    }
    /* end of kludge */
    return VLC_SUCCESS;
}