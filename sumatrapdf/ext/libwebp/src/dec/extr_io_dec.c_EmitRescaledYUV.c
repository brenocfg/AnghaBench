#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  WebPRescaler ;
struct TYPE_7__ {int /*<<< orphan*/ * const scaler_v; int /*<<< orphan*/ * const scaler_u; TYPE_1__* output; int /*<<< orphan*/ * scaler_y; } ;
typedef  TYPE_2__ WebPDecParams ;
struct TYPE_8__ {int mb_h; int /*<<< orphan*/  uv_stride; scalar_t__ v; scalar_t__ u; int /*<<< orphan*/  y_stride; scalar_t__ y; int /*<<< orphan*/  mb_w; int /*<<< orphan*/  width; int /*<<< orphan*/ * a; } ;
typedef  TYPE_3__ VP8Io ;
struct TYPE_6__ {int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int Rescale (scalar_t__,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ * const) ; 
 scalar_t__ WebPIsAlphaMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPMultRows (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int EmitRescaledYUV(const VP8Io* const io, WebPDecParams* const p) {
  const int mb_h = io->mb_h;
  const int uv_mb_h = (mb_h + 1) >> 1;
  WebPRescaler* const scaler = p->scaler_y;
  int num_lines_out = 0;
  if (WebPIsAlphaMode(p->output->colorspace) && io->a != NULL) {
    // Before rescaling, we premultiply the luma directly into the io->y
    // internal buffer. This is OK since these samples are not used for
    // intra-prediction (the top samples are saved in cache_y_/u_/v_).
    // But we need to cast the const away, though.
    WebPMultRows((uint8_t*)io->y, io->y_stride,
                 io->a, io->width, io->mb_w, mb_h, 0);
  }
  num_lines_out = Rescale(io->y, io->y_stride, mb_h, scaler);
  Rescale(io->u, io->uv_stride, uv_mb_h, p->scaler_u);
  Rescale(io->v, io->uv_stride, uv_mb_h, p->scaler_v);
  return num_lines_out;
}