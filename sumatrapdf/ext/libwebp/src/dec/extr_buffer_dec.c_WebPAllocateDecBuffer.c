#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int crop_width; int crop_height; int crop_left; int crop_top; int scaled_width; int scaled_height; scalar_t__ flip; scalar_t__ use_scaling; scalar_t__ use_cropping; } ;
typedef  TYPE_1__ WebPDecoderOptions ;
struct TYPE_8__ {int width; int height; } ;
typedef  TYPE_2__ WebPDecBuffer ;
typedef  scalar_t__ VP8StatusCode ;

/* Variables and functions */
 scalar_t__ AllocateBuffer (TYPE_2__* const) ; 
 scalar_t__ VP8_STATUS_INVALID_PARAM ; 
 scalar_t__ VP8_STATUS_OK ; 
 scalar_t__ WebPFlipBuffer (TYPE_2__* const) ; 
 int /*<<< orphan*/  WebPRescalerGetScaledDimensions (int,int,int*,int*) ; 

VP8StatusCode WebPAllocateDecBuffer(int width, int height,
                                    const WebPDecoderOptions* const options,
                                    WebPDecBuffer* const buffer) {
  VP8StatusCode status;
  if (buffer == NULL || width <= 0 || height <= 0) {
    return VP8_STATUS_INVALID_PARAM;
  }
  if (options != NULL) {    // First, apply options if there is any.
    if (options->use_cropping) {
      const int cw = options->crop_width;
      const int ch = options->crop_height;
      const int x = options->crop_left & ~1;
      const int y = options->crop_top & ~1;
      if (x < 0 || y < 0 || cw <= 0 || ch <= 0 ||
          x + cw > width || y + ch > height) {
        return VP8_STATUS_INVALID_PARAM;   // out of frame boundary.
      }
      width = cw;
      height = ch;
    }

    if (options->use_scaling) {
#if !defined(WEBP_REDUCE_SIZE)
      int scaled_width = options->scaled_width;
      int scaled_height = options->scaled_height;
      if (!WebPRescalerGetScaledDimensions(
              width, height, &scaled_width, &scaled_height)) {
        return VP8_STATUS_INVALID_PARAM;
      }
      width = scaled_width;
      height = scaled_height;
#else
      return VP8_STATUS_INVALID_PARAM;   // rescaling not supported
#endif
    }
  }
  buffer->width = width;
  buffer->height = height;

  // Then, allocate buffer for real.
  status = AllocateBuffer(buffer);
  if (status != VP8_STATUS_OK) return status;

  // Use the stride trick if vertical flip is needed.
  if (options != NULL && options->flip) {
    status = WebPFlipBuffer(buffer);
  }
  return status;
}