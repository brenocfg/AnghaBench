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
struct TYPE_6__ {scalar_t__ last_y; int /*<<< orphan*/  scaler_v; int /*<<< orphan*/  scaler_u; int /*<<< orphan*/  scaler_y; } ;
typedef  TYPE_1__ WebPDecParams ;
struct TYPE_7__ {int mb_h; int y_stride; int uv_stride; scalar_t__ v; scalar_t__ u; scalar_t__ y; } ;
typedef  TYPE_2__ VP8Io ;

/* Variables and functions */
 scalar_t__ ExportRGB (TYPE_1__* const,scalar_t__) ; 
 scalar_t__ WebPRescaleNeededLines (int /*<<< orphan*/ ,int const) ; 
 int WebPRescalerImport (int /*<<< orphan*/ ,int const,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int EmitRescaledRGB(const VP8Io* const io, WebPDecParams* const p) {
  const int mb_h = io->mb_h;
  const int uv_mb_h = (mb_h + 1) >> 1;
  int j = 0, uv_j = 0;
  int num_lines_out = 0;
  while (j < mb_h) {
    const int y_lines_in =
        WebPRescalerImport(p->scaler_y, mb_h - j,
                           io->y + j * io->y_stride, io->y_stride);
    j += y_lines_in;
    if (WebPRescaleNeededLines(p->scaler_u, uv_mb_h - uv_j)) {
      const int u_lines_in =
          WebPRescalerImport(p->scaler_u, uv_mb_h - uv_j,
                             io->u + uv_j * io->uv_stride, io->uv_stride);
      const int v_lines_in =
          WebPRescalerImport(p->scaler_v, uv_mb_h - uv_j,
                             io->v + uv_j * io->uv_stride, io->uv_stride);
      (void)v_lines_in;   // remove a gcc warning
      assert(u_lines_in == v_lines_in);
      uv_j += u_lines_in;
    }
    num_lines_out += ExportRGB(p, p->last_y + num_lines_out);
  }
  return num_lines_out;
}