#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  top_derr_; int /*<<< orphan*/  percent_; int /*<<< orphan*/  lf_stats_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_7__ {int /*<<< orphan*/  top_derr_; int /*<<< orphan*/ * u_left_; int /*<<< orphan*/ * v_left_; int /*<<< orphan*/ * y_left_; scalar_t__ yuv_left_mem_; int /*<<< orphan*/  percent0_; int /*<<< orphan*/  lf_stats_; int /*<<< orphan*/ * yuv_out2_; int /*<<< orphan*/ * yuv_p_; int /*<<< orphan*/ * yuv_out_; int /*<<< orphan*/ * yuv_in_; scalar_t__ yuv_mem_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  VP8IteratorReset (TYPE_2__* const) ; 
 scalar_t__ WEBP_ALIGN (scalar_t__) ; 
 int YUV_SIZE_ENC ; 

void VP8IteratorInit(VP8Encoder* const enc, VP8EncIterator* const it) {
  it->enc_ = enc;
  it->yuv_in_   = (uint8_t*)WEBP_ALIGN(it->yuv_mem_);
  it->yuv_out_  = it->yuv_in_ + YUV_SIZE_ENC;
  it->yuv_out2_ = it->yuv_out_ + YUV_SIZE_ENC;
  it->yuv_p_    = it->yuv_out2_ + YUV_SIZE_ENC;
  it->lf_stats_ = enc->lf_stats_;
  it->percent0_ = enc->percent_;
  it->y_left_ = (uint8_t*)WEBP_ALIGN(it->yuv_left_mem_ + 1);
  it->u_left_ = it->y_left_ + 16 + 16;
  it->v_left_ = it->u_left_ + 16;
  it->top_derr_ = enc->top_derr_;
  VP8IteratorReset(it);
}