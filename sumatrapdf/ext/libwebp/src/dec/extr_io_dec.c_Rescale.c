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
typedef  int /*<<< orphan*/  WebPRescaler ;

/* Variables and functions */
 scalar_t__ WebPRescalerExport (int /*<<< orphan*/ * const) ; 
 int WebPRescalerImport (int /*<<< orphan*/ * const,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int Rescale(const uint8_t* src, int src_stride,
                   int new_lines, WebPRescaler* const wrk) {
  int num_lines_out = 0;
  while (new_lines > 0) {    // import new contributions of source rows.
    const int lines_in = WebPRescalerImport(wrk, new_lines, src, src_stride);
    src += lines_in * src_stride;
    new_lines -= lines_in;
    num_lines_out += WebPRescalerExport(wrk);    // emit output row(s)
  }
  return num_lines_out;
}