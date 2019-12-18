#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int den; unsigned int num; } ;
typedef  TYPE_2__ vlc_rational_t ;
struct TYPE_14__ {unsigned int plane_count; unsigned int pixel_size; TYPE_1__* p; } ;
typedef  TYPE_3__ vlc_chroma_description_t ;
struct TYPE_15__ {scalar_t__ i_width; scalar_t__ i_height; int i_visible_width; int i_visible_height; scalar_t__ i_x_offset; scalar_t__ i_y_offset; int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_4__ video_format_t ;
struct TYPE_16__ {int i_pixel_pitch; unsigned int i_lines; int i_visible_lines; unsigned int i_pitch; int i_visible_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_5__ plane_t ;
struct TYPE_17__ {unsigned int i_planes; int i_nb_fields; TYPE_5__* p; int /*<<< orphan*/  format; } ;
typedef  TYPE_6__ picture_t ;
struct TYPE_12__ {TYPE_2__ w; TYPE_2__ h; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_5__*) ; 
 unsigned int INT_MAX ; 
 unsigned int LCM (unsigned int,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int add_overflow (scalar_t__,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  video_format_CopyCrop (int /*<<< orphan*/ *,TYPE_4__ const*) ; 
 int /*<<< orphan*/  video_format_Setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* vlc_fourcc_GetChromaDescription (int /*<<< orphan*/ ) ; 

int picture_Setup( picture_t *p_picture, const video_format_t *restrict fmt )
{
    const vlc_chroma_description_t *p_dsc =
        vlc_fourcc_GetChromaDescription( fmt->i_chroma );
    if( unlikely(!p_dsc) )
        return VLC_EGENERIC;

    /* Store default values */
    p_picture->i_planes = 0;
    for( unsigned i = 0; i < ARRAY_SIZE(p_picture->p); i++ )
    {
        plane_t *p = &p_picture->p[i];
        p->p_pixels = NULL;
        p->i_pixel_pitch = 0;
    }

    p_picture->i_nb_fields = 2;

    video_format_Setup( &p_picture->format, fmt->i_chroma, fmt->i_width, fmt->i_height,
                        fmt->i_visible_width, fmt->i_visible_height,
                        fmt->i_sar_num, fmt->i_sar_den );
    if( fmt->i_x_offset < fmt->i_width &&
        fmt->i_y_offset < fmt->i_height &&
        fmt->i_visible_width  > 0 && fmt->i_x_offset + fmt->i_visible_width  <= fmt->i_width &&
        fmt->i_visible_height > 0 && fmt->i_y_offset + fmt->i_visible_height <= fmt->i_height )
        video_format_CopyCrop( &p_picture->format, fmt );

    /* We want V (width/height) to respect:
        (V * p_dsc->p[i].w.i_num) % p_dsc->p[i].w.i_den == 0
        (V * p_dsc->p[i].w.i_num/p_dsc->p[i].w.i_den * p_dsc->i_pixel_size) % 16 == 0
       Which is respected if you have
       V % lcm( p_dsc->p[0..planes].w.i_den * 16) == 0
    */
    unsigned i_modulo_w = 1;
    unsigned i_modulo_h = 1;
    unsigned i_ratio_h  = 1;

    for( unsigned i = 0; i < p_dsc->plane_count; i++ )
    {
        i_modulo_w = LCM( i_modulo_w, 16 * p_dsc->p[i].w.den );
        i_modulo_h = LCM( i_modulo_h, 16 * p_dsc->p[i].h.den );
        if( i_ratio_h < p_dsc->p[i].h.den )
            i_ratio_h = p_dsc->p[i].h.den;
    }
    i_modulo_h = LCM( i_modulo_h, 32 );

    unsigned width, height;

    if (unlikely(add_overflow(fmt->i_width, i_modulo_w - 1, &width))
     || unlikely(add_overflow(fmt->i_height, i_modulo_h - 1, &height)))
        return VLC_EGENERIC;

    width = width / i_modulo_w * i_modulo_w;
    height = height / i_modulo_h * i_modulo_h;

    /* plane_t uses 'int'. */
    if (unlikely(width > INT_MAX) || unlikely(height > INT_MAX))
        return VLC_EGENERIC;

    for( unsigned i = 0; i < p_dsc->plane_count; i++ )
    {
        plane_t *p = &p_picture->p[i];
        const vlc_rational_t *h = &p_dsc->p[i].h;
        const vlc_rational_t *w = &p_dsc->p[i].w;

        /* A plane cannot be over-sampled. This could lead to overflow. */
        assert(h->den >= h->num);
        assert(w->den >= w->num);

        p->i_lines = height * h->num / h->den;
        p->i_visible_lines = (fmt->i_visible_height + (h->den - 1)) / h->den * h->num;

        p->i_pitch = width * w->num / w->den * p_dsc->pixel_size;
        p->i_visible_pitch = (fmt->i_visible_width + (w->den - 1)) / w->den * w->num
                             * p_dsc->pixel_size;
        p->i_pixel_pitch = p_dsc->pixel_size;

        assert( (p->i_pitch % 16) == 0 );
    }
    p_picture->i_planes = p_dsc->plane_count;

    return VLC_SUCCESS;
}