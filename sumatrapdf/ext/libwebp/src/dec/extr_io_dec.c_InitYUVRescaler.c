#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  rescaler_t ;
struct TYPE_10__ {int /*<<< orphan*/  a_stride; int /*<<< orphan*/  a; int /*<<< orphan*/  v_stride; int /*<<< orphan*/  v; int /*<<< orphan*/  u_stride; int /*<<< orphan*/  u; int /*<<< orphan*/  y_stride; int /*<<< orphan*/  y; } ;
typedef  TYPE_3__ WebPYUVABuffer ;
typedef  int /*<<< orphan*/  WebPRescaler ;
struct TYPE_11__ {int /*<<< orphan*/  emit_alpha; int /*<<< orphan*/ * scaler_a; int /*<<< orphan*/  emit; int /*<<< orphan*/ * scaler_v; int /*<<< orphan*/ * scaler_u; int /*<<< orphan*/ * scaler_y; int /*<<< orphan*/ * memory; TYPE_2__* output; } ;
typedef  TYPE_4__ WebPDecParams ;
struct TYPE_12__ {int scaled_width; int scaled_height; int mb_w; int mb_h; } ;
typedef  TYPE_5__ VP8Io ;
struct TYPE_8__ {TYPE_3__ YUVA; } ;
struct TYPE_9__ {TYPE_1__ u; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitRescaledAlphaYUV ; 
 int /*<<< orphan*/  EmitRescaledYUV ; 
 scalar_t__ WEBP_ALIGN (int /*<<< orphan*/  const*) ; 
 int const WEBP_ALIGN_CST ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 
 int WebPIsAlphaMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPRescalerInit (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPSafeMalloc (unsigned long long,size_t) ; 

__attribute__((used)) static int InitYUVRescaler(const VP8Io* const io, WebPDecParams* const p) {
  const int has_alpha = WebPIsAlphaMode(p->output->colorspace);
  const WebPYUVABuffer* const buf = &p->output->u.YUVA;
  const int out_width  = io->scaled_width;
  const int out_height = io->scaled_height;
  const int uv_out_width  = (out_width + 1) >> 1;
  const int uv_out_height = (out_height + 1) >> 1;
  const int uv_in_width  = (io->mb_w + 1) >> 1;
  const int uv_in_height = (io->mb_h + 1) >> 1;
  const size_t work_size = 2 * out_width;   // scratch memory for luma rescaler
  const size_t uv_work_size = 2 * uv_out_width;  // and for each u/v ones
  size_t tmp_size, rescaler_size;
  rescaler_t* work;
  WebPRescaler* scalers;
  const int num_rescalers = has_alpha ? 4 : 3;

  tmp_size = (work_size + 2 * uv_work_size) * sizeof(*work);
  if (has_alpha) {
    tmp_size += work_size * sizeof(*work);
  }
  rescaler_size = num_rescalers * sizeof(*p->scaler_y) + WEBP_ALIGN_CST;

  p->memory = WebPSafeMalloc(1ULL, tmp_size + rescaler_size);
  if (p->memory == NULL) {
    return 0;   // memory error
  }
  work = (rescaler_t*)p->memory;

  scalers = (WebPRescaler*)WEBP_ALIGN((const uint8_t*)work + tmp_size);
  p->scaler_y = &scalers[0];
  p->scaler_u = &scalers[1];
  p->scaler_v = &scalers[2];
  p->scaler_a = has_alpha ? &scalers[3] : NULL;

  WebPRescalerInit(p->scaler_y, io->mb_w, io->mb_h,
                   buf->y, out_width, out_height, buf->y_stride, 1,
                   work);
  WebPRescalerInit(p->scaler_u, uv_in_width, uv_in_height,
                   buf->u, uv_out_width, uv_out_height, buf->u_stride, 1,
                   work + work_size);
  WebPRescalerInit(p->scaler_v, uv_in_width, uv_in_height,
                   buf->v, uv_out_width, uv_out_height, buf->v_stride, 1,
                   work + work_size + uv_work_size);
  p->emit = EmitRescaledYUV;

  if (has_alpha) {
    WebPRescalerInit(p->scaler_a, io->mb_w, io->mb_h,
                     buf->a, out_width, out_height, buf->a_stride, 1,
                     work + work_size + 2 * uv_work_size);
    p->emit_alpha = EmitRescaledAlphaYUV;
    WebPInitAlphaProcessing();
  }
  return 1;
}