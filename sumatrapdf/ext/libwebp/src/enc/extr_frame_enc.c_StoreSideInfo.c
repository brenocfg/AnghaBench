#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {int* extra_info; int extra_info_type; int /*<<< orphan*/ * stats; } ;
typedef  TYPE_2__ WebPPicture ;
struct TYPE_10__ {int type_; scalar_t__ skip_; int segment_; int uv_mode_; int alpha_; } ;
typedef  TYPE_3__ VP8MBInfo ;
struct TYPE_11__ {int* block_count_; size_t mb_w_; TYPE_1__* dqm_; TYPE_2__* pic_; } ;
typedef  TYPE_4__ VP8Encoder ;
struct TYPE_12__ {size_t x_; size_t y_; int* preds_; scalar_t__ yuv_out_; scalar_t__ uv_bits_; scalar_t__ luma_bits_; TYPE_3__* mb_; TYPE_4__* enc_; } ;
typedef  TYPE_5__ VP8EncIterator ;
struct TYPE_8__ {int quant_; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetBlock (scalar_t__,int,int) ; 
 int /*<<< orphan*/  StoreSSE (TYPE_5__ const* const) ; 
 scalar_t__ U_OFF_ENC ; 
 scalar_t__ V_OFF_ENC ; 
 scalar_t__ Y_OFF_ENC ; 

__attribute__((used)) static void StoreSideInfo(const VP8EncIterator* const it) {
  VP8Encoder* const enc = it->enc_;
  const VP8MBInfo* const mb = it->mb_;
  WebPPicture* const pic = enc->pic_;

  if (pic->stats != NULL) {
    StoreSSE(it);
    enc->block_count_[0] += (mb->type_ == 0);
    enc->block_count_[1] += (mb->type_ == 1);
    enc->block_count_[2] += (mb->skip_ != 0);
  }

  if (pic->extra_info != NULL) {
    uint8_t* const info = &pic->extra_info[it->x_ + it->y_ * enc->mb_w_];
    switch (pic->extra_info_type) {
      case 1: *info = mb->type_; break;
      case 2: *info = mb->segment_; break;
      case 3: *info = enc->dqm_[mb->segment_].quant_; break;
      case 4: *info = (mb->type_ == 1) ? it->preds_[0] : 0xff; break;
      case 5: *info = mb->uv_mode_; break;
      case 6: {
        const int b = (int)((it->luma_bits_ + it->uv_bits_ + 7) >> 3);
        *info = (b > 255) ? 255 : b; break;
      }
      case 7: *info = mb->alpha_; break;
      default: *info = 0; break;
    }
  }
#if SEGMENT_VISU  // visualize segments and prediction modes
  SetBlock(it->yuv_out_ + Y_OFF_ENC, mb->segment_ * 64, 16);
  SetBlock(it->yuv_out_ + U_OFF_ENC, it->preds_[0] * 64, 8);
  SetBlock(it->yuv_out_ + V_OFF_ENC, mb->uv_mode_ * 64, 8);
#endif
}