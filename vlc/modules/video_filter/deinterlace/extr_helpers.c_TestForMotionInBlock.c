#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ int_fast16_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ T ; 
 scalar_t__ abs (scalar_t__) ; 

__attribute__((used)) static int TestForMotionInBlock( uint8_t *p_pix_p, uint8_t *p_pix_c,
                                 int i_pitch_prev, int i_pitch_curr,
                                 int* pi_top, int* pi_bot )
{
/* Pixel luma/chroma difference threshold to detect motion. */

    int32_t i_motion = 0;
    int32_t i_top_motion = 0;
    int32_t i_bot_motion = 0;

    for( int y = 0; y < 8; ++y )
    {
        uint8_t *pc = p_pix_c;
        uint8_t *pp = p_pix_p;
        int score = 0;
        for( int x = 0; x < 8; ++x )
        {
            int_fast16_t C = abs((*pc) - (*pp));
            if( C > T )
                ++score;

            ++pc;
            ++pp;
        }

        i_motion += score;
        if( y % 2 == 0 )
            i_top_motion += score;
        else
            i_bot_motion += score;

        p_pix_c += i_pitch_curr;
        p_pix_p += i_pitch_prev;
    }

    /* Field motion thresholds.

       Empirical value - works better in practice than the "4" that
       would be consistent with the full-block threshold.

       Especially the opening scene of The Third ep. 1 (just after the OP)
       works better with this. It also fixes some talking scenes in
       Stellvia ep. 1, where the cadence would otherwise catch on incorrectly,
       leading to more interlacing artifacts than by just using the emergency
       mode frame composer.
    */
    (*pi_top) = ( i_top_motion >= 8 );
    (*pi_bot) = ( i_bot_motion >= 8 );

    /* Full-block threshold = (8*8)/8: motion is detected if 1/8 of the block
       changes "enough". */
    return (i_motion >= 8);
}