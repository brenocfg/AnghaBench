#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int id_; TYPE_2__* mb_data_; } ;
typedef  TYPE_1__ VP8ThreadContext ;
struct TYPE_6__ {scalar_t__ dither_; } ;
typedef  TYPE_2__ VP8MBData ;
struct TYPE_7__ {int tl_mb_x_; int br_mb_x_; int cache_uv_stride_; int /*<<< orphan*/  dithering_rg_; int /*<<< orphan*/ * cache_v_; int /*<<< orphan*/ * cache_u_; TYPE_1__ thread_ctx_; int /*<<< orphan*/  dither_; } ;
typedef  TYPE_3__ VP8Decoder ;

/* Variables and functions */
 int /*<<< orphan*/  Dither8x8 (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int const,scalar_t__) ; 
 scalar_t__ MIN_DITHER_AMP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DitherRow(VP8Decoder* const dec) {
  int mb_x;
  assert(dec->dither_);
  for (mb_x = dec->tl_mb_x_; mb_x < dec->br_mb_x_; ++mb_x) {
    const VP8ThreadContext* const ctx = &dec->thread_ctx_;
    const VP8MBData* const data = ctx->mb_data_ + mb_x;
    const int cache_id = ctx->id_;
    const int uv_bps = dec->cache_uv_stride_;
    if (data->dither_ >= MIN_DITHER_AMP) {
      uint8_t* const u_dst = dec->cache_u_ + cache_id * 8 * uv_bps + mb_x * 8;
      uint8_t* const v_dst = dec->cache_v_ + cache_id * 8 * uv_bps + mb_x * 8;
      Dither8x8(&dec->dithering_rg_, u_dst, uv_bps, data->dither_);
      Dither8x8(&dec->dithering_rg_, v_dst, uv_bps, data->dither_);
    }
  }
}