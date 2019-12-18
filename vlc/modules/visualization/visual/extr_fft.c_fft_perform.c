#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sound_sample ;
struct TYPE_3__ {int /*<<< orphan*/  imag; int /*<<< orphan*/  real; int /*<<< orphan*/  sintable; int /*<<< orphan*/  costable; int /*<<< orphan*/  bitReverse; } ;
typedef  TYPE_1__ fft_state ;

/* Variables and functions */
 int /*<<< orphan*/  fft_calculate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fft_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  fft_prepare (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fft_perform(const sound_sample *input, float *output, fft_state *state) {
    /* Convert data from sound format to be ready for FFT */
    fft_prepare(input, state->real, state->imag, state->bitReverse );

    /* Do the actual FFT */
    fft_calculate(state->real, state->imag, state->costable, state->sintable);

    /* Convert the FFT output into intensities */
    fft_output(state->real, state->imag, output);
}