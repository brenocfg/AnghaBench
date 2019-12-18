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
typedef  int /*<<< orphan*/  rescaler_t ;
typedef  int /*<<< orphan*/  WebPRescaler ;

/* Variables and functions */
 int /*<<< orphan*/  WebPRescalerExport (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPRescalerImport (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  WebPRescalerInit (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void RescalePlane(const uint8_t* src,
                         int src_width, int src_height, int src_stride,
                         uint8_t* dst,
                         int dst_width, int dst_height, int dst_stride,
                         rescaler_t* const work,
                         int num_channels) {
  WebPRescaler rescaler;
  int y = 0;
  WebPRescalerInit(&rescaler, src_width, src_height,
                   dst, dst_width, dst_height, dst_stride,
                   num_channels, work);
  while (y < src_height) {
    y += WebPRescalerImport(&rescaler, src_height - y,
                            src + y * src_stride, src_stride);
    WebPRescalerExport(&rescaler);
  }
}