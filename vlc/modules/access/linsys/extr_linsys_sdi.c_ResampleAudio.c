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
typedef  float int16_t ;

/* Variables and functions */

__attribute__((used)) static void ResampleAudio( int16_t *p_out, int16_t *p_in,
                           unsigned int i_out, unsigned int i_in )
{
    unsigned int i_remainder = 0;
    float f_last_sample = (float)*p_in / 32768.f;

    *p_out = *p_in;
    p_out += 2;
    p_in += 2;

    for ( unsigned int i = 1; i < i_in; i++ )
    {
        float f_in = (float)*p_in / 32768.f;
        while ( i_remainder < i_out )
        {
            float f_out = f_last_sample;
            f_out += (f_in - f_last_sample) * i_remainder / i_out;
            if ( f_out >= 1.f ) *p_out = 32767;
            else if ( f_out < -1.f ) *p_out = -32768;
            else *p_out = f_out * 32768.f;
            p_out += 2;
            i_remainder += i_in;
        }

        f_last_sample = f_in;
        p_in += 2;
        i_remainder -= i_out;
    }
}