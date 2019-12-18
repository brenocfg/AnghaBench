#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
typedef  int const uint64_t ;
typedef  int uint32_t ;
typedef  int const rescaler_t ;
struct TYPE_4__ {unsigned int* dst; int* irow; int dst_width; int num_channels; int* frow; int y_expand; scalar_t__ y_sub; int /*<<< orphan*/  fy_scale; int /*<<< orphan*/  y_accum; } ;
typedef  TYPE_1__ WebPRescaler ;

/* Variables and functions */
 scalar_t__ MULT_FIX (int const,int /*<<< orphan*/ ) ; 
 int const ROUNDER ; 
 int WEBP_RESCALER_FRAC (int /*<<< orphan*/ ,scalar_t__) ; 
 int const WEBP_RESCALER_ONE ; 
 int const WEBP_RESCALER_RFIX ; 
 int /*<<< orphan*/  WebPRescalerOutputDone (TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 

void WebPRescalerExportRowExpand_C(WebPRescaler* const wrk) {
  int x_out;
  uint8_t* const dst = wrk->dst;
  rescaler_t* const irow = wrk->irow;
  const int x_out_max = wrk->dst_width * wrk->num_channels;
  const rescaler_t* const frow = wrk->frow;
  assert(!WebPRescalerOutputDone(wrk));
  assert(wrk->y_accum <= 0);
  assert(wrk->y_expand);
  assert(wrk->y_sub != 0);
  if (wrk->y_accum == 0) {
    for (x_out = 0; x_out < x_out_max; ++x_out) {
      const uint32_t J = frow[x_out];
      const int v = (int)MULT_FIX(J, wrk->fy_scale);
      dst[x_out] = (v > 255) ? 255u : (uint8_t)v;
    }
  } else {
    const uint32_t B = WEBP_RESCALER_FRAC(-wrk->y_accum, wrk->y_sub);
    const uint32_t A = (uint32_t)(WEBP_RESCALER_ONE - B);
    for (x_out = 0; x_out < x_out_max; ++x_out) {
      const uint64_t I = (uint64_t)A * frow[x_out]
                       + (uint64_t)B * irow[x_out];
      const uint32_t J = (uint32_t)((I + ROUNDER) >> WEBP_RESCALER_RFIX);
      const int v = (int)MULT_FIX(J, wrk->fy_scale);
      dst[x_out] = (v > 255) ? 255u : (uint8_t)v;
    }
  }
}