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
typedef  int /*<<< orphan*/  rescaler_t ;
typedef  int /*<<< orphan*/  WebPRescaler ;
struct TYPE_7__ {int /*<<< orphan*/  emit_alpha_row; TYPE_1__* output; int /*<<< orphan*/  emit_alpha; int /*<<< orphan*/ * scaler_a; int /*<<< orphan*/  emit; int /*<<< orphan*/ * scaler_v; int /*<<< orphan*/ * scaler_u; int /*<<< orphan*/ * scaler_y; int /*<<< orphan*/ * memory; } ;
typedef  TYPE_2__ WebPDecParams ;
struct TYPE_8__ {int scaled_width; int scaled_height; int mb_w; int mb_h; } ;
typedef  TYPE_3__ VP8Io ;
struct TYPE_6__ {scalar_t__ colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitRescaledAlphaRGB ; 
 int /*<<< orphan*/  EmitRescaledRGB ; 
 int /*<<< orphan*/  ExportAlpha ; 
 int /*<<< orphan*/  ExportAlphaRGBA4444 ; 
 scalar_t__ MODE_RGBA_4444 ; 
 scalar_t__ MODE_rgbA_4444 ; 
 scalar_t__ WEBP_ALIGN (int /*<<< orphan*/  const*) ; 
 int const WEBP_ALIGN_CST ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 
 int /*<<< orphan*/  WebPInitYUV444Converters () ; 
 int WebPIsAlphaMode (scalar_t__) ; 
 int /*<<< orphan*/  WebPRescalerInit (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPSafeMalloc (unsigned long long,size_t) ; 

__attribute__((used)) static int InitRGBRescaler(const VP8Io* const io, WebPDecParams* const p) {
  const int has_alpha = WebPIsAlphaMode(p->output->colorspace);
  const int out_width  = io->scaled_width;
  const int out_height = io->scaled_height;
  const int uv_in_width  = (io->mb_w + 1) >> 1;
  const int uv_in_height = (io->mb_h + 1) >> 1;
  const size_t work_size = 2 * out_width;   // scratch memory for one rescaler
  rescaler_t* work;  // rescalers work area
  uint8_t* tmp;   // tmp storage for scaled YUV444 samples before RGB conversion
  size_t tmp_size1, tmp_size2, total_size, rescaler_size;
  WebPRescaler* scalers;
  const int num_rescalers = has_alpha ? 4 : 3;

  tmp_size1 = 3 * work_size;
  tmp_size2 = 3 * out_width;
  if (has_alpha) {
    tmp_size1 += work_size;
    tmp_size2 += out_width;
  }
  total_size = tmp_size1 * sizeof(*work) + tmp_size2 * sizeof(*tmp);
  rescaler_size = num_rescalers * sizeof(*p->scaler_y) + WEBP_ALIGN_CST;

  p->memory = WebPSafeMalloc(1ULL, total_size + rescaler_size);
  if (p->memory == NULL) {
    return 0;   // memory error
  }
  work = (rescaler_t*)p->memory;
  tmp = (uint8_t*)(work + tmp_size1);

  scalers = (WebPRescaler*)WEBP_ALIGN((const uint8_t*)work + total_size);
  p->scaler_y = &scalers[0];
  p->scaler_u = &scalers[1];
  p->scaler_v = &scalers[2];
  p->scaler_a = has_alpha ? &scalers[3] : NULL;

  WebPRescalerInit(p->scaler_y, io->mb_w, io->mb_h,
                   tmp + 0 * out_width, out_width, out_height, 0, 1,
                   work + 0 * work_size);
  WebPRescalerInit(p->scaler_u, uv_in_width, uv_in_height,
                   tmp + 1 * out_width, out_width, out_height, 0, 1,
                   work + 1 * work_size);
  WebPRescalerInit(p->scaler_v, uv_in_width, uv_in_height,
                   tmp + 2 * out_width, out_width, out_height, 0, 1,
                   work + 2 * work_size);
  p->emit = EmitRescaledRGB;
  WebPInitYUV444Converters();

  if (has_alpha) {
    WebPRescalerInit(p->scaler_a, io->mb_w, io->mb_h,
                     tmp + 3 * out_width, out_width, out_height, 0, 1,
                     work + 3 * work_size);
    p->emit_alpha = EmitRescaledAlphaRGB;
    if (p->output->colorspace == MODE_RGBA_4444 ||
        p->output->colorspace == MODE_rgbA_4444) {
      p->emit_alpha_row = ExportAlphaRGBA4444;
    } else {
      p->emit_alpha_row = ExportAlpha;
    }
    WebPInitAlphaProcessing();
  }
  return 1;
}