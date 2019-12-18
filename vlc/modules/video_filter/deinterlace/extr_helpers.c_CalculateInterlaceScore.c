#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {scalar_t__ i_planes; TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
typedef  scalar_t__ int_fast32_t ;
typedef  int int32_t ;
struct TYPE_7__ {int i_visible_lines; int i_pitch; scalar_t__* p_pixels; int /*<<< orphan*/  i_visible_pitch; } ;

/* Variables and functions */
 int CalculateInterlaceScoreMMX (TYPE_2__ const*,TYPE_2__ const*) ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ T ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_CPU_MMXEXT () ; 

int CalculateInterlaceScore( const picture_t* p_pic_top,
                             const picture_t* p_pic_bot )
{
    /*
        We use the comb metric from the IVTC filter of Transcode 1.1.5.
        This was found to work better for the particular purpose of IVTC
        than RenderX()'s comb metric.

        Note that we *must not* subsample at all in order to catch interlacing
        in telecined frames with localized motion (e.g. anime with characters
        talking, where only mouths move and everything else stays still.)
    */

    assert( p_pic_top != NULL );
    assert( p_pic_bot != NULL );

    if( p_pic_top->i_planes != p_pic_bot->i_planes )
        return -1;

#ifdef CAN_COMPILE_MMXEXT
    if (vlc_CPU_MMXEXT())
        return CalculateInterlaceScoreMMX( p_pic_top, p_pic_bot );
#endif

    int32_t i_score = 0;

    for( int i_plane = 0 ; i_plane < p_pic_top->i_planes ; ++i_plane )
    {
        /* Sanity check */
        if( p_pic_top->p[i_plane].i_visible_lines !=
            p_pic_bot->p[i_plane].i_visible_lines )
            return -1;

        const int i_lasty = p_pic_top->p[i_plane].i_visible_lines-1;
        const int w = FFMIN( p_pic_top->p[i_plane].i_visible_pitch,
                             p_pic_bot->p[i_plane].i_visible_pitch );

        /* Current line / neighbouring lines picture pointers */
        const picture_t *cur = p_pic_bot;
        const picture_t *ngh = p_pic_top;
        int wc = cur->p[i_plane].i_pitch;
        int wn = ngh->p[i_plane].i_pitch;

        /* Transcode 1.1.5 only checks every other line. Checking every line
           works better for anime, which may contain horizontal,
           one pixel thick cartoon outlines.
        */
        for( int y = 1; y < i_lasty; ++y )
        {
            uint8_t *p_c = &cur->p[i_plane].p_pixels[y*wc];     /* this line */
            uint8_t *p_p = &ngh->p[i_plane].p_pixels[(y-1)*wn]; /* prev line */
            uint8_t *p_n = &ngh->p[i_plane].p_pixels[(y+1)*wn]; /* next line */

            for( int x = 0; x < w; ++x )
            {
                /* Worst case: need 17 bits for "comb". */
                int_fast32_t C = *p_c;
                int_fast32_t P = *p_p;
                int_fast32_t N = *p_n;

                /* Comments in Transcode's filter_ivtc.c attribute this
                   combing metric to Gunnar Thalin.

                    The idea is that if the picture is interlaced, both
                    expressions will have the same sign, and this comes
                    up positive. The value T = 100 has been chosen such
                    that a pixel difference of 10 (on average) will
                    trigger the detector.
                */
                int_fast32_t comb = (P - C) * (N - C);
                if( comb > T )
                    ++i_score;

                ++p_c;
                ++p_p;
                ++p_n;
            }

            /* Now the other field - swap current and neighbour pictures */
            const picture_t *tmp = cur;
            cur = ngh;
            ngh = tmp;
            int tmp_pitch = wc;
            wc = wn;
            wn = tmp_pitch;
        }
    }

    return i_score;
}