#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/ * emit_alpha; int /*<<< orphan*/ * emit; int /*<<< orphan*/ * tmp_u; int /*<<< orphan*/ * tmp_v; int /*<<< orphan*/ * tmp_y; int /*<<< orphan*/ * memory; int /*<<< orphan*/  options; int /*<<< orphan*/ * emit_alpha_row; TYPE_1__* output; } ;
typedef  TYPE_2__ WebPDecParams ;
typedef  scalar_t__ WEBP_CSP_MODE ;
struct TYPE_12__ {int mb_w; scalar_t__ fancy_upsampling; scalar_t__ use_scaling; scalar_t__ opaque; } ;
typedef  TYPE_3__ VP8Io ;
struct TYPE_10__ {scalar_t__ colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EmitAlphaRGB ; 
 int /*<<< orphan*/ * EmitAlphaRGBA4444 ; 
 int /*<<< orphan*/ * EmitAlphaYUV ; 
 int /*<<< orphan*/ * EmitFancyRGB ; 
 int /*<<< orphan*/ * EmitSampledRGB ; 
 int /*<<< orphan*/ * EmitYUV ; 
 int InitRGBRescaler (TYPE_3__*,TYPE_2__* const) ; 
 int InitYUVRescaler (TYPE_3__*,TYPE_2__* const) ; 
 scalar_t__ const MODE_RGBA_4444 ; 
 int /*<<< orphan*/  MODE_YUV ; 
 int /*<<< orphan*/  MODE_YUVA ; 
 scalar_t__ const MODE_rgbA_4444 ; 
 int /*<<< orphan*/  WebPInitAlphaProcessing () ; 
 int /*<<< orphan*/  WebPInitSamplers () ; 
 int /*<<< orphan*/  WebPInitUpsamplers () ; 
 int /*<<< orphan*/  WebPIoInitFromOptions (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int WebPIsAlphaMode (scalar_t__ const) ; 
 scalar_t__ WebPIsPremultipliedMode (scalar_t__ const) ; 
 int WebPIsRGBMode (scalar_t__ const) ; 
 int /*<<< orphan*/ * WebPSafeMalloc (unsigned long long,size_t) ; 

__attribute__((used)) static int CustomSetup(VP8Io* io) {
  WebPDecParams* const p = (WebPDecParams*)io->opaque;
  const WEBP_CSP_MODE colorspace = p->output->colorspace;
  const int is_rgb = WebPIsRGBMode(colorspace);
  const int is_alpha = WebPIsAlphaMode(colorspace);

  p->memory = NULL;
  p->emit = NULL;
  p->emit_alpha = NULL;
  p->emit_alpha_row = NULL;
  if (!WebPIoInitFromOptions(p->options, io, is_alpha ? MODE_YUV : MODE_YUVA)) {
    return 0;
  }
  if (is_alpha && WebPIsPremultipliedMode(colorspace)) {
    WebPInitUpsamplers();
  }
  if (io->use_scaling) {
#if !defined(WEBP_REDUCE_SIZE)
    const int ok = is_rgb ? InitRGBRescaler(io, p) : InitYUVRescaler(io, p);
    if (!ok) {
      return 0;    // memory error
    }
#else
    return 0;   // rescaling support not compiled
#endif
  } else {
    if (is_rgb) {
      WebPInitSamplers();
      p->emit = EmitSampledRGB;   // default
      if (io->fancy_upsampling) {
#ifdef FANCY_UPSAMPLING
        const int uv_width = (io->mb_w + 1) >> 1;
        p->memory = WebPSafeMalloc(1ULL, (size_t)(io->mb_w + 2 * uv_width));
        if (p->memory == NULL) {
          return 0;   // memory error.
        }
        p->tmp_y = (uint8_t*)p->memory;
        p->tmp_u = p->tmp_y + io->mb_w;
        p->tmp_v = p->tmp_u + uv_width;
        p->emit = EmitFancyRGB;
        WebPInitUpsamplers();
#endif
      }
    } else {
      p->emit = EmitYUV;
    }
    if (is_alpha) {  // need transparency output
      p->emit_alpha =
          (colorspace == MODE_RGBA_4444 || colorspace == MODE_rgbA_4444) ?
              EmitAlphaRGBA4444
          : is_rgb ? EmitAlphaRGB
          : EmitAlphaYUV;
      if (is_rgb) {
        WebPInitAlphaProcessing();
      }
    }
  }

  return 1;
}