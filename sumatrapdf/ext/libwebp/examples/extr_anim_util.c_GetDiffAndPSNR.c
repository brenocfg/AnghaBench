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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Accumulate (int const,int const,double*,double*) ; 
 int kNumChannels ; 
 double log (int) ; 

void GetDiffAndPSNR(const uint8_t rgba1[], const uint8_t rgba2[],
                    uint32_t width, uint32_t height, int premultiply,
                    int* const max_diff, double* const psnr) {
  const uint32_t stride = width * kNumChannels;
  const int kAlphaChannel = kNumChannels - 1;
  double f_max_diff = 0.;
  double sse = 0.;
  uint32_t x, y;
  for (y = 0; y < height; ++y) {
    for (x = 0; x < stride; x += kNumChannels) {
      int k;
      const size_t offset = (size_t)y * stride + x;
      const int alpha1 = rgba1[offset + kAlphaChannel];
      const int alpha2 = rgba2[offset + kAlphaChannel];
      Accumulate(alpha1, alpha2, &f_max_diff, &sse);
      if (!premultiply) {
        for (k = 0; k < kAlphaChannel; ++k) {
          Accumulate(rgba1[offset + k], rgba2[offset + k], &f_max_diff, &sse);
        }
      } else {
        // premultiply R/G/B channels with alpha value
        for (k = 0; k < kAlphaChannel; ++k) {
          Accumulate(rgba1[offset + k] * alpha1 / 255.,
                     rgba2[offset + k] * alpha2 / 255.,
                     &f_max_diff, &sse);
        }
      }
    }
  }
  *max_diff = (int)f_max_diff;
  if (*max_diff == 0) {
    *psnr = 99.;  // PSNR when images are identical.
  } else {
    sse /= stride * height;
    *psnr = 4.3429448 * log(255. * 255. / sse);
  }
}