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
 int FFT_BUFFER_SIZE ; 
 unsigned int FFT_BUFFER_SIZE_LOG ; 

__attribute__((used)) static void fft_calculate(float * re, float * im, const float *costable, const float *sintable )
{
    unsigned int i, j, k;
    unsigned int exchanges;
    float fact_real, fact_imag;
    float tmp_real, tmp_imag;
    unsigned int factfact;

    /* Set up some variables to reduce calculation in the loops */
    exchanges = 1;
    factfact = FFT_BUFFER_SIZE / 2;

    /* Loop through the divide and conquer steps */
    for(i = FFT_BUFFER_SIZE_LOG; i != 0; i--) {
        /* In this step, we have 2 ^ (i - 1) exchange groups, each with
         * 2 ^ (FFT_BUFFER_SIZE_LOG - i) exchanges
         */
        /* Loop through the exchanges in a group */
        for(j = 0; j != exchanges; j++) {
            /* Work out factor for this exchange
             * factor ^ (exchanges) = -1
             * So, real = cos(j * PI / exchanges),
             *     imag = sin(j * PI / exchanges)
             */
            fact_real = costable[j * factfact];
            fact_imag = sintable[j * factfact];

            /* Loop through all the exchange groups */
            for(k = j; k < FFT_BUFFER_SIZE; k += exchanges << 1) {
                int k1 = k + exchanges;
                tmp_real = fact_real * re[k1] - fact_imag * im[k1];
                tmp_imag = fact_real * im[k1] + fact_imag * re[k1];
                re[k1] = re[k] - tmp_real;
                im[k1] = im[k] - tmp_imag;
                re[k]  += tmp_real;
                im[k]  += tmp_imag;
            }
        }
        exchanges <<= 1;
        factfact >>= 1;
    }
}