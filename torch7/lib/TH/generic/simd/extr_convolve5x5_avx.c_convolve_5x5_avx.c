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
 int /*<<< orphan*/  CLEAR_AVX () ; 
 int /*<<< orphan*/  convolve_5x5_16x16_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_1_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_2_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_32x32_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_4_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_64x64_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_6_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_8x8_avx (float*,float*,float*,long,long,long) ; 
 int /*<<< orphan*/  convolve_5x5_sse (float*,float*,float*,long,long,long,long) ; 

void convolve_5x5_avx(float* output, float* input, float* kernel, long outRows, long outCols, long outStride, long inCols) {
  long ic = inCols;
  long yy = 0;
  float* t_ = input;
  float* r_ = output;
  float* k_ = kernel;

  if((outRows == 64) && (outCols == 64)) {
    convolve_5x5_64x64_avx(output, input, kernel, outRows, outStride, inCols);
    return;
  }

  if((outRows == 32) && (outCols == 32)) {
    convolve_5x5_32x32_avx(output, input, kernel, outRows, outStride, inCols);
    return;
  }

  if((outRows == 16) && (outCols == 16)) {
    convolve_5x5_16x16_avx(output, input, kernel, outRows, outStride, inCols);
    return;
  }

  if((outRows == 8) && (outCols == 8)) {
    convolve_5x5_8x8_avx(output, input, kernel, outRows, outStride, inCols);
    return;
  }

  for(; yy < (outRows / 6 ) * 6; yy += 6) {
    float *pi_ = t_ + yy*ic;
    float *pw_ = k_;
    float *pis_ = pi_;
    convolve_5x5_6_avx(r_, pis_, pw_, outCols, outStride, ic);
    r_ += (outStride * 6);
  }

  // more than 2 rows left to process and we ended up on a non-multiple of 4
  if((yy < (outRows & 0xFFFFFFFE)) && ((yy % 4) != 0)) {
    // process 2 rows to align on the next multiple of 4 rows (because we were a multiple of 6 after the previous loop)
    float *pi_ = t_ + yy*ic;
    float *pw_ = k_;
    float *pis_ = pi_;
    convolve_5x5_2_avx(r_, pis_, pw_, outCols, outStride, ic);
    r_ += (outStride * 2);
    yy += 2;
  }

  for(; yy < (outRows & 0xFFFFFFFC); yy += 4) {
    float *pi_ = t_ + yy*ic;
    float *pw_ = k_;
    float *pis_ = pi_;
    convolve_5x5_4_avx(r_, pis_, pw_, outCols, outStride, ic);
    r_ += (outStride * 4);
  }

  for(; yy < (outRows & 0xFFFFFFFE); yy += 2) {
    float *pi_ = t_ + yy*ic;
    float *pw_ = k_;
    float *pis_ = pi_;
    convolve_5x5_2_avx(r_, pis_, pw_, outCols, outStride, ic);
    r_ += (outStride * 2);
  }

  for(; yy < outRows; yy += 1) {
    float *pi_ = t_ + yy*ic;
    float *pw_ = k_;
    float *pis_ = pi_;
    convolve_5x5_1_avx(r_, pis_, pw_, outCols, outStride, ic);
    r_ += (outStride * 1);
  }

  long procCols = outCols & 0xFFFFFFF8; // avx version processes 8 cols at a time
  long remCols = outCols - procCols;

  //process the rest using sse
  if( remCols > 0) {
    CLEAR_AVX();
    convolve_5x5_sse(&output[procCols], &input[procCols], kernel, outRows, remCols, outStride, inCols);
  }
}