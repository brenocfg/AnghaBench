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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ VP8SSIMGet (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ VP8SSIMGetClipped (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int,int,int) ; 
 int VP8_SSIM_KERNEL ; 

__attribute__((used)) static double AccumulateSSIM(const uint8_t* src, int src_stride,
                             const uint8_t* ref, int ref_stride,
                             int w, int h) {
  const int w0 = (w < VP8_SSIM_KERNEL) ? w : VP8_SSIM_KERNEL;
  const int w1 = w - VP8_SSIM_KERNEL - 1;
  const int h0 = (h < VP8_SSIM_KERNEL) ? h : VP8_SSIM_KERNEL;
  const int h1 = h - VP8_SSIM_KERNEL - 1;
  int x, y;
  double sum = 0.;
  for (y = 0; y < h0; ++y) {
    for (x = 0; x < w; ++x) {
      sum += VP8SSIMGetClipped(src, src_stride, ref, ref_stride, x, y, w, h);
    }
  }
  for (; y < h1; ++y) {
    for (x = 0; x < w0; ++x) {
      sum += VP8SSIMGetClipped(src, src_stride, ref, ref_stride, x, y, w, h);
    }
    for (; x < w1; ++x) {
      const int off1 = x - VP8_SSIM_KERNEL + (y - VP8_SSIM_KERNEL) * src_stride;
      const int off2 = x - VP8_SSIM_KERNEL + (y - VP8_SSIM_KERNEL) * ref_stride;
      sum += VP8SSIMGet(src + off1, src_stride, ref + off2, ref_stride);
    }
    for (; x < w; ++x) {
      sum += VP8SSIMGetClipped(src, src_stride, ref, ref_stride, x, y, w, h);
    }
  }
  for (; y < h; ++y) {
    for (x = 0; x < w; ++x) {
      sum += VP8SSIMGetClipped(src, src_stride, ref, ref_stride, x, y, w, h);
    }
  }
  return sum;
}