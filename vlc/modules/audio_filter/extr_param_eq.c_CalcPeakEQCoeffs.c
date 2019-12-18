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
 scalar_t__ M_PI ; 
 int cosf (float) ; 
 float powf (int,float) ; 
 int sinf (float) ; 

__attribute__((used)) static void CalcPeakEQCoeffs( float f0, float Q, float gainDB, float Fs,
                              float *coeffs )
{
    float A;
    float w0;
    float alpha;
    float b0, b1, b2;
    float a0, a1, a2;

    // Provide sane limits to avoid overflow
    if (Q < 0.1f) Q = 0.1f;
    if (Q > 100) Q = 100;
    if (f0 > Fs/2*0.95f) f0 = Fs/2*0.95f;
    if (gainDB < -40) gainDB = -40;
    if (gainDB > 40) gainDB = 40;
 
    A = powf(10, gainDB/40);
    w0 = 2*((float)M_PI)*f0/Fs;
    alpha = sinf(w0)/(2*Q);
 
    b0 = 1 + alpha*A;
    b1 = -2*cosf(w0);
    b2 = 1 - alpha*A;
    a0 = 1 + alpha/A;
    a1 = -2*cosf(w0);
    a2 = 1 - alpha/A;
 
    // Store values to coeffs and normalize by 1/a0
    coeffs[0] = b0/a0;
    coeffs[1] = b1/a0;
    coeffs[2] = b2/a0;
    coeffs[3] = a1/a0;
    coeffs[4] = a2/a0;
}