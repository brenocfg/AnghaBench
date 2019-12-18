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
struct TYPE_4__ {int mb_w_; int mb_h_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_5__ {int x_; int y_; int /*<<< orphan*/ * uv_top_; int /*<<< orphan*/ * y_top_; int /*<<< orphan*/ * v_left_; int /*<<< orphan*/ * u_left_; int /*<<< orphan*/ * y_left_; int /*<<< orphan*/ * yuv_out_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int BPS ; 
 int U_OFF_ENC ; 
 int Y_OFF_ENC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int) ; 

void VP8IteratorSaveBoundary(VP8EncIterator* const it) {
  VP8Encoder* const enc = it->enc_;
  const int x = it->x_, y = it->y_;
  const uint8_t* const ysrc = it->yuv_out_ + Y_OFF_ENC;
  const uint8_t* const uvsrc = it->yuv_out_ + U_OFF_ENC;
  if (x < enc->mb_w_ - 1) {   // left
    int i;
    for (i = 0; i < 16; ++i) {
      it->y_left_[i] = ysrc[15 + i * BPS];
    }
    for (i = 0; i < 8; ++i) {
      it->u_left_[i] = uvsrc[7 + i * BPS];
      it->v_left_[i] = uvsrc[15 + i * BPS];
    }
    // top-left (before 'top'!)
    it->y_left_[-1] = it->y_top_[15];
    it->u_left_[-1] = it->uv_top_[0 + 7];
    it->v_left_[-1] = it->uv_top_[8 + 7];
  }
  if (y < enc->mb_h_ - 1) {  // top
    memcpy(it->y_top_, ysrc + 15 * BPS, 16);
    memcpy(it->uv_top_, uvsrc + 7 * BPS, 8 + 8);
  }
}