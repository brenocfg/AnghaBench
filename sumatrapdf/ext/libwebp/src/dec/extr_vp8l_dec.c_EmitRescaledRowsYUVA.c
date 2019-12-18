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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int last_out_row_; TYPE_2__* rescaler; } ;
typedef  TYPE_1__ VP8LDecoder ;
struct TYPE_7__ {int /*<<< orphan*/  src_width; } ;

/* Variables and functions */
 scalar_t__ ExportYUVA (TYPE_1__ const* const,int) ; 
 int /*<<< orphan*/  WebPMultARGBRows (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int WebPRescaleNeededLines (TYPE_2__*,int const) ; 
 int WebPRescalerImport (TYPE_2__*,int const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int EmitRescaledRowsYUVA(const VP8LDecoder* const dec,
                                uint8_t* in, int in_stride, int mb_h) {
  int num_lines_in = 0;
  int y_pos = dec->last_out_row_;
  while (num_lines_in < mb_h) {
    const int lines_left = mb_h - num_lines_in;
    const int needed_lines = WebPRescaleNeededLines(dec->rescaler, lines_left);
    int lines_imported;
    WebPMultARGBRows(in, in_stride, dec->rescaler->src_width, needed_lines, 0);
    lines_imported =
        WebPRescalerImport(dec->rescaler, lines_left, in, in_stride);
    assert(lines_imported == needed_lines);
    num_lines_in += lines_imported;
    in += needed_lines * in_stride;
    y_pos += ExportYUVA(dec, y_pos);
  }
  return y_pos;
}