#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ use_cropping; int crop_width; int crop_height; int crop_left; int crop_top; scalar_t__ use_scaling; int scaled_width; int scaled_height; int /*<<< orphan*/  no_fancy_upsampling; scalar_t__ bypass_filtering; } ;
typedef  TYPE_1__ WebPDecoderOptions ;
typedef  int /*<<< orphan*/  WEBP_CSP_MODE ;
struct TYPE_6__ {int width; int height; int use_cropping; int crop_left; int crop_top; int crop_right; int crop_bottom; int mb_w; int mb_h; int use_scaling; int scaled_width; int scaled_height; int bypass_filtering; int fancy_upsampling; } ;
typedef  TYPE_2__ VP8Io ;

/* Variables and functions */
 int /*<<< orphan*/  WebPIsRGBMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPRescalerGetScaledDimensions (int,int,int*,int*) ; 

int WebPIoInitFromOptions(const WebPDecoderOptions* const options,
                          VP8Io* const io, WEBP_CSP_MODE src_colorspace) {
  const int W = io->width;
  const int H = io->height;
  int x = 0, y = 0, w = W, h = H;

  // Cropping
  io->use_cropping = (options != NULL) && (options->use_cropping > 0);
  if (io->use_cropping) {
    w = options->crop_width;
    h = options->crop_height;
    x = options->crop_left;
    y = options->crop_top;
    if (!WebPIsRGBMode(src_colorspace)) {   // only snap for YUV420
      x &= ~1;
      y &= ~1;
    }
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > W || y + h > H) {
      return 0;  // out of frame boundary error
    }
  }
  io->crop_left   = x;
  io->crop_top    = y;
  io->crop_right  = x + w;
  io->crop_bottom = y + h;
  io->mb_w = w;
  io->mb_h = h;

  // Scaling
  io->use_scaling = (options != NULL) && (options->use_scaling > 0);
  if (io->use_scaling) {
    int scaled_width = options->scaled_width;
    int scaled_height = options->scaled_height;
    if (!WebPRescalerGetScaledDimensions(w, h, &scaled_width, &scaled_height)) {
      return 0;
    }
    io->scaled_width = scaled_width;
    io->scaled_height = scaled_height;
  }

  // Filter
  io->bypass_filtering = (options != NULL) && options->bypass_filtering;

  // Fancy upsampler
#ifdef FANCY_UPSAMPLING
  io->fancy_upsampling = (options == NULL) || (!options->no_fancy_upsampling);
#endif

  if (io->use_scaling) {
    // disable filter (only for large downscaling ratio).
    io->bypass_filtering = (io->scaled_width < W * 3 / 4) &&
                           (io->scaled_height < H * 3 / 4);
    io->fancy_upsampling = 0;
  }
  return 1;
}