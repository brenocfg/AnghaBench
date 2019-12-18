#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ const uint32_t ;
typedef  int /*<<< orphan*/  rescaler_t ;
struct TYPE_3__ {int x_expand; int y_expand; int src_width; int src_height; int dst_width; int dst_height; int dst_stride; int num_channels; int x_add; int x_sub; int y_add; int y_sub; int y_accum; scalar_t__ fxy_scale; int /*<<< orphan*/ * frow; int /*<<< orphan*/ * irow; void* fy_scale; void* fx_scale; int /*<<< orphan*/ * dst; scalar_t__ dst_y; scalar_t__ src_y; } ;
typedef  TYPE_1__ WebPRescaler ;

/* Variables and functions */
 void* WEBP_RESCALER_FRAC (int,scalar_t__) ; 
 scalar_t__ WEBP_RESCALER_ONE ; 
 int /*<<< orphan*/  WebPRescalerDspInit () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

void WebPRescalerInit(WebPRescaler* const wrk, int src_width, int src_height,
                      uint8_t* const dst,
                      int dst_width, int dst_height, int dst_stride,
                      int num_channels, rescaler_t* const work) {
  const int x_add = src_width, x_sub = dst_width;
  const int y_add = src_height, y_sub = dst_height;
  wrk->x_expand = (src_width < dst_width);
  wrk->y_expand = (src_height < dst_height);
  wrk->src_width = src_width;
  wrk->src_height = src_height;
  wrk->dst_width = dst_width;
  wrk->dst_height = dst_height;
  wrk->src_y = 0;
  wrk->dst_y = 0;
  wrk->dst = dst;
  wrk->dst_stride = dst_stride;
  wrk->num_channels = num_channels;

  // for 'x_expand', we use bilinear interpolation
  wrk->x_add = wrk->x_expand ? (x_sub - 1) : x_add;
  wrk->x_sub = wrk->x_expand ? (x_add - 1) : x_sub;
  if (!wrk->x_expand) {  // fx_scale is not used otherwise
    wrk->fx_scale = WEBP_RESCALER_FRAC(1, wrk->x_sub);
  }
  // vertical scaling parameters
  wrk->y_add = wrk->y_expand ? y_add - 1 : y_add;
  wrk->y_sub = wrk->y_expand ? y_sub - 1 : y_sub;
  wrk->y_accum = wrk->y_expand ? wrk->y_sub : wrk->y_add;
  if (!wrk->y_expand) {
    // This is WEBP_RESCALER_FRAC(dst_height, x_add * y_add) without the cast.
    // Its value is <= WEBP_RESCALER_ONE, because dst_height <= wrk->y_add, and
    // wrk->x_add >= 1;
    const uint64_t ratio =
        (uint64_t)dst_height * WEBP_RESCALER_ONE / (wrk->x_add * wrk->y_add);
    if (ratio != (uint32_t)ratio) {
      // When ratio == WEBP_RESCALER_ONE, we can't represent the ratio with the
      // current fixed-point precision. This happens when src_height ==
      // wrk->y_add (which == src_height), and wrk->x_add == 1.
      // => We special-case fxy_scale = 0, in WebPRescalerExportRow().
      wrk->fxy_scale = 0;
    } else {
      wrk->fxy_scale = (uint32_t)ratio;
    }
    wrk->fy_scale = WEBP_RESCALER_FRAC(1, wrk->y_sub);
  } else {
    wrk->fy_scale = WEBP_RESCALER_FRAC(1, wrk->x_add);
    // wrk->fxy_scale is unused here.
  }
  wrk->irow = work;
  wrk->frow = work + num_channels * dst_width;
  memset(work, 0, 2 * dst_width * num_channels * sizeof(*work));

  WebPRescalerDspInit();
}