#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int dst_width; scalar_t__ dst; } ;
typedef  TYPE_1__ WebPRescaler ;
typedef  int /*<<< orphan*/  WEBP_CSP_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LConvertFromBGRA (int /*<<< orphan*/ * const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  WebPMultARGBRow (int /*<<< orphan*/ * const,int const,int) ; 
 int /*<<< orphan*/  WebPRescalerExportRow (TYPE_1__* const) ; 
 scalar_t__ WebPRescalerHasPendingOutput (TYPE_1__* const) ; 

__attribute__((used)) static int Export(WebPRescaler* const rescaler, WEBP_CSP_MODE colorspace,
                  int rgba_stride, uint8_t* const rgba) {
  uint32_t* const src = (uint32_t*)rescaler->dst;
  const int dst_width = rescaler->dst_width;
  int num_lines_out = 0;
  while (WebPRescalerHasPendingOutput(rescaler)) {
    uint8_t* const dst = rgba + num_lines_out * rgba_stride;
    WebPRescalerExportRow(rescaler);
    WebPMultARGBRow(src, dst_width, 1);
    VP8LConvertFromBGRA(src, dst_width, colorspace, dst);
    ++num_lines_out;
  }
  return num_lines_out;
}