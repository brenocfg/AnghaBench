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

/* Variables and functions */

void ProcessEQ( const float *src, float *dest, float *state,
                unsigned channels, unsigned samples, const float *coeffs,
                unsigned eqCount )
{
    unsigned i, chn, eq;
    float   b0, b1, b2, a1, a2;
    float   x, y = 0;
    const float *src1 = src;
    float *dest1 = dest;

    for (i = 0; i < samples; i++)
    {
        float *state1 = state;
        for (chn = 0; chn < channels; chn++)
        {
            const float *coeffs1 = coeffs;
            x = *src1++;
            /* Direct form 1 IIRs */
            for (eq = 0; eq < eqCount; eq++)
            {
                b0 = coeffs1[0];
                b1 = coeffs1[1];
                b2 = coeffs1[2];
                a1 = coeffs1[3];
                a2 = coeffs1[4];
                coeffs1 += 5;
                y = x*b0 + state1[0]*b1 + state1[1]*b2 - state1[2]*a1 - state1[3]*a2;
                state1[1] = state1[0];
                state1[0] = x;
                state1[3] = state1[2];
                state1[2] = y;
                x = y;
                state1 += 4;
            }
            *dest1++ = y;
        }
    }
}