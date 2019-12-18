#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int dst_width; scalar_t__ dst; } ;
typedef  TYPE_1__ WebPRescaler ;
struct TYPE_7__ {int /*<<< orphan*/  output_; TYPE_1__* rescaler; } ;
typedef  TYPE_2__ VP8LDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertToYUVA (int /*<<< orphan*/ * const,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPMultARGBRow (int /*<<< orphan*/ * const,int const,int) ; 
 int /*<<< orphan*/  WebPRescalerExportRow (TYPE_1__* const) ; 
 scalar_t__ WebPRescalerHasPendingOutput (TYPE_1__* const) ; 

__attribute__((used)) static int ExportYUVA(const VP8LDecoder* const dec, int y_pos) {
  WebPRescaler* const rescaler = dec->rescaler;
  uint32_t* const src = (uint32_t*)rescaler->dst;
  const int dst_width = rescaler->dst_width;
  int num_lines_out = 0;
  while (WebPRescalerHasPendingOutput(rescaler)) {
    WebPRescalerExportRow(rescaler);
    WebPMultARGBRow(src, dst_width, 1);
    ConvertToYUVA(src, dst_width, y_pos, dec->output_);
    ++y_pos;
    ++num_lines_out;
  }
  return num_lines_out;
}