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
typedef  int /*<<< orphan*/  sound_sample ;

/* Variables and functions */
 unsigned int FFT_BUFFER_SIZE ; 

__attribute__((used)) static void fft_prepare( const sound_sample *input, float * re, float * im,
                         const unsigned int *bitReverse ) {
    unsigned int i;
    float *p_real = re;
    float *p_imag = im;

    /* Get input, in reverse bit order */
    for(i = 0; i < FFT_BUFFER_SIZE; i++)
    {
        *p_real++ = input[bitReverse[i]];
        *p_imag++ = 0;
    }
}