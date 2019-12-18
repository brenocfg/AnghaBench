#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {scalar_t__ i_chroma; } ;
struct TYPE_7__ {TYPE_1__* p; TYPE_5__ format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_6__ {int* p_pixels; int i_visible_lines; int i_pitch; int i_visible_pitch; } ;

/* Variables and functions */
 int FIX (double) ; 
 int /*<<< orphan*/  GetPackedRgbIndexes (TYPE_5__*,int*,int*,int*) ; 
 int ONE_HALF ; 
 int SCALEBITS ; 
 scalar_t__ VLC_CODEC_RGB32 ; 
 int vlc_uint8 (int) ; 

__attribute__((used)) static void RVSepia( picture_t *p_pic, picture_t *p_outpic, int i_intensity )
{
#define SCALEBITS 10
#define ONE_HALF  (1 << (SCALEBITS - 1))
#define FIX(x)    ((int) ((x) * (1<<SCALEBITS) + 0.5))
    uint8_t *p_in, *p_in_end, *p_line_end, *p_out;
    bool b_isRV32 = p_pic->format.i_chroma == VLC_CODEC_RGB32;
    int i_rindex = 0, i_gindex = 1, i_bindex = 2;

    GetPackedRgbIndexes( &p_outpic->format, &i_rindex, &i_gindex, &i_bindex );

    p_in = p_pic->p[0].p_pixels;
    p_in_end = p_in + p_pic->p[0].i_visible_lines
        * p_pic->p[0].i_pitch;
    p_out = p_outpic->p[0].p_pixels;

    /* Precompute values constant for this certain i_intensity, using the same
     * formula as YUV functions above */
    uint8_t r_intensity = (( FIX( 1.40200 * 255.0 / 224.0 ) * (i_intensity * 14)
                        + ONE_HALF )) >> SCALEBITS;
    uint8_t g_intensity = (( - FIX(0.34414*255.0/224.0) * ( - i_intensity / 6 )
                        - FIX( 0.71414 * 255.0 / 224.0) * ( i_intensity * 14 )
                        + ONE_HALF )) >> SCALEBITS;
    uint8_t b_intensity = (( FIX( 1.77200 * 255.0 / 224.0) * ( - i_intensity / 6 )
                        + ONE_HALF )) >> SCALEBITS;

    while (p_in < p_in_end)
    {
        p_line_end = p_in + p_pic->p[0].i_visible_pitch;
        while (p_in < p_line_end)
        {
            /* do sepia: this calculation is based on the formula to calculate
             * YUV->RGB and RGB->YUV (in filter_picture.h) mode and that
             * y = y - y/4 + intensity/4 . As Y is the only channel that changes
             * through the whole image. After that, precomputed values are added
             * for each RGB channel and saved in the output image.
             * FIXME: needs cleanup */
            uint8_t i_y = ((( 66 * p_in[i_rindex] + 129 * p_in[i_gindex] +  25
                      * p_in[i_bindex] + 128 ) >> 8 ) * FIX(255.0/219.0))
                      - (((( 66 * p_in[i_rindex] + 129 * p_in[i_gindex] + 25
                      * p_in[i_bindex] + 128 ) >> 8 )
                      * FIX( 255.0 / 219.0 )) >> 2 ) + ( i_intensity >> 2 );
            p_out[i_rindex] = vlc_uint8(i_y + r_intensity);
            p_out[i_gindex] = vlc_uint8(i_y + g_intensity);
            p_out[i_bindex] = vlc_uint8(i_y + b_intensity);
            p_in += 3;
            p_out += 3;
            /* for rv32 we take 4 chunks at the time */
            if (b_isRV32) {
            /* alpha channel stays the same */
            *p_out++ = *p_in++;
            }
        }

        p_in += p_pic->p[0].i_pitch - p_pic->p[0].i_visible_pitch;
        p_out += p_outpic->p[0].i_pitch
            - p_outpic->p[0].i_visible_pitch;
    }
#undef SCALEBITS
#undef ONE_HALF
#undef FIX
}