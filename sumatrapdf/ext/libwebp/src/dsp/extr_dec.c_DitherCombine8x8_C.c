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

/* Variables and functions */
 int const VP8_DITHER_AMP_CENTER ; 
 int const VP8_DITHER_DESCALE ; 
 int const VP8_DITHER_DESCALE_ROUNDER ; 
 int clip_8b (int) ; 

__attribute__((used)) static void DitherCombine8x8_C(const uint8_t* dither, uint8_t* dst,
                               int dst_stride) {
  int i, j;
  for (j = 0; j < 8; ++j) {
    for (i = 0; i < 8; ++i) {
      const int delta0 = dither[i] - VP8_DITHER_AMP_CENTER;
      const int delta1 =
          (delta0 + VP8_DITHER_DESCALE_ROUNDER) >> VP8_DITHER_DESCALE;
      dst[i] = clip_8b((int)dst[i] + delta1);
    }
    dst += dst_stride;
    dither += 8;
  }
}