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
typedef  int uint8_t ;
struct TYPE_4__ {int num_channels; int dst_width; int x_expand; int x_add; int src_width; int* frow; scalar_t__ x_sub; } ;
typedef  TYPE_1__ WebPRescaler ;

/* Variables and functions */
 int /*<<< orphan*/  WebPRescalerInputDone (TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 

void WebPRescalerImportRowExpand_C(WebPRescaler* const wrk,
                                   const uint8_t* src) {
  const int x_stride = wrk->num_channels;
  const int x_out_max = wrk->dst_width * wrk->num_channels;
  int channel;
  assert(!WebPRescalerInputDone(wrk));
  assert(wrk->x_expand);
  for (channel = 0; channel < x_stride; ++channel) {
    int x_in = channel;
    int x_out = channel;
    // simple bilinear interpolation
    int accum = wrk->x_add;
    int left = src[x_in];
    int right = (wrk->src_width > 1) ? src[x_in + x_stride] : left;
    x_in += x_stride;
    while (1) {
      wrk->frow[x_out] = right * wrk->x_add + (left - right) * accum;
      x_out += x_stride;
      if (x_out >= x_out_max) break;
      accum -= wrk->x_sub;
      if (accum < 0) {
        left = right;
        x_in += x_stride;
        assert(x_in < wrk->src_width * x_stride);
        right = src[x_in];
        accum += wrk->x_add;
      }
    }
    assert(wrk->x_sub == 0 /* <- special case for src_width=1 */ || accum == 0);
  }
}