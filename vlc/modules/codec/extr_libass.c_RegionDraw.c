#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {int i_width; int i_height; } ;
struct TYPE_10__ {int i_x; int i_y; TYPE_2__ fmt; TYPE_1__* p_picture; } ;
typedef  TYPE_3__ subpicture_region_t ;
struct TYPE_11__ {int* p_pixels; int i_pitch; int i_lines; int i_visible_pitch; int i_visible_lines; } ;
typedef  TYPE_4__ plane_t ;
struct TYPE_12__ {int const dst_x; int const w; int const dst_y; int const h; int color; unsigned int* bitmap; int stride; struct TYPE_12__* next; } ;
struct TYPE_8__ {TYPE_4__* p; } ;
typedef  TYPE_5__ ASS_Image ;

/* Variables and functions */
 int* P (int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void RegionDraw( subpicture_region_t *p_region, ASS_Image *p_img )
{
    const plane_t *p = &p_region->p_picture->p[0];
    const int i_x = p_region->i_x;
    const int i_y = p_region->i_y;
    const int i_width  = p_region->fmt.i_width;
    const int i_height = p_region->fmt.i_height;

    memset( p->p_pixels, 0x00, p->i_pitch * p->i_lines );
    for( ; p_img != NULL; p_img = p_img->next )
    {
        if( p_img->dst_x < i_x || p_img->dst_x + p_img->w > i_x + i_width ||
            p_img->dst_y < i_y || p_img->dst_y + p_img->h > i_y + i_height )
            continue;

        const unsigned r = (p_img->color >> 24)&0xff;
        const unsigned g = (p_img->color >> 16)&0xff;
        const unsigned b = (p_img->color >>  8)&0xff;
        const unsigned a = (p_img->color      )&0xff;
        int x, y;

        for( y = 0; y < p_img->h; y++ )
        {
            for( x = 0; x < p_img->w; x++ )
            {
                const unsigned alpha = p_img->bitmap[y*p_img->stride+x];
                const unsigned an = (255 - a) * alpha / 255;

                uint8_t *p_rgba = &p->p_pixels[(y+p_img->dst_y-i_y) * p->i_pitch + 4 * (x+p_img->dst_x-i_x)];
                const unsigned ao = p_rgba[3];

                /* Native endianness, but RGBA ordering */
                if( ao == 0 )
                {
                    /* Optimized but the else{} will produce the same result */
                    p_rgba[0] = r;
                    p_rgba[1] = g;
                    p_rgba[2] = b;
                    p_rgba[3] = an;
                }
                else
                {
                    p_rgba[3] = 255 - ( 255 - p_rgba[3] ) * ( 255 - an ) / 255;
                    if( p_rgba[3] != 0 )
                    {
                        p_rgba[0] = ( p_rgba[0] * ao * (255-an) / 255 + r * an ) / p_rgba[3];
                        p_rgba[1] = ( p_rgba[1] * ao * (255-an) / 255 + g * an ) / p_rgba[3];
                        p_rgba[2] = ( p_rgba[2] * ao * (255-an) / 255 + b * an ) / p_rgba[3];
                    }
                }
            }
        }
    }

#ifdef DEBUG_REGION
    /* XXX Draw a box for debug */
#define P(x,y) ((uint32_t*)&p->p_pixels[(y)*p->i_pitch + 4*(x)])
    for( int y = 0; y < p->i_lines; y++ )
        *P(0,y) = *P(p->i_visible_pitch/4-1,y) = 0xff000000;
    for( int x = 0; x < p->i_visible_pitch; x++ )
        *P(x/4,0) = *P(x/4,p->i_visible_lines-1) = 0xff000000;
#undef P
#endif
}