#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int sse_count_; int /*<<< orphan*/ * sse_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_5__ {int /*<<< orphan*/ * yuv_out_; int /*<<< orphan*/ * yuv_in_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int U_OFF_ENC ; 
 scalar_t__ VP8SSE16x16 (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 
 scalar_t__ VP8SSE8x8 (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 
 int V_OFF_ENC ; 
 int Y_OFF_ENC ; 

__attribute__((used)) static void StoreSSE(const VP8EncIterator* const it) {
  VP8Encoder* const enc = it->enc_;
  const uint8_t* const in = it->yuv_in_;
  const uint8_t* const out = it->yuv_out_;
  // Note: not totally accurate at boundary. And doesn't include in-loop filter.
  enc->sse_[0] += VP8SSE16x16(in + Y_OFF_ENC, out + Y_OFF_ENC);
  enc->sse_[1] += VP8SSE8x8(in + U_OFF_ENC, out + U_OFF_ENC);
  enc->sse_[2] += VP8SSE8x8(in + V_OFF_ENC, out + V_OFF_ENC);
  enc->sse_count_ += 16 * 16;
}