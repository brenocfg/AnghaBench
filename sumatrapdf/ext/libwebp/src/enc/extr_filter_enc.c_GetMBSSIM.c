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
 int /*<<< orphan*/  BPS ; 
 int U_OFF_ENC ; 
 scalar_t__ VP8SSIMGetClipped (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int VP8_SSIM_KERNEL ; 
 int V_OFF_ENC ; 
 int Y_OFF_ENC ; 

__attribute__((used)) static double GetMBSSIM(const uint8_t* yuv1, const uint8_t* yuv2) {
  int x, y;
  double sum = 0.;

  // compute SSIM in a 10 x 10 window
  for (y = VP8_SSIM_KERNEL; y < 16 - VP8_SSIM_KERNEL; y++) {
    for (x = VP8_SSIM_KERNEL; x < 16 - VP8_SSIM_KERNEL; x++) {
      sum += VP8SSIMGetClipped(yuv1 + Y_OFF_ENC, BPS, yuv2 + Y_OFF_ENC, BPS,
                               x, y, 16, 16);
    }
  }
  for (x = 1; x < 7; x++) {
    for (y = 1; y < 7; y++) {
      sum += VP8SSIMGetClipped(yuv1 + U_OFF_ENC, BPS, yuv2 + U_OFF_ENC, BPS,
                               x, y, 8, 8);
      sum += VP8SSIMGetClipped(yuv1 + V_OFF_ENC, BPS, yuv2 + V_OFF_ENC, BPS,
                               x, y, 8, 8);
    }
  }
  return sum;
}