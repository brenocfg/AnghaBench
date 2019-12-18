#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_20__ {scalar_t__ error_; } ;
struct TYPE_19__ {int mb_w_; int mb_h_; int num_parts_; TYPE_4__* pic_; scalar_t__ alpha_data_size_; int /*<<< orphan*/  proba_; int /*<<< orphan*/  filter_hdr_; TYPE_3__ bw_; } ;
typedef  TYPE_2__ VP8Encoder ;
typedef  TYPE_3__ VP8BitWriter ;
struct TYPE_21__ {TYPE_1__* stats; } ;
struct TYPE_18__ {int* header_bytes; int alpha_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PutFilterHeader (TYPE_3__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PutQuant (TYPE_3__* const,TYPE_2__* const) ; 
 int /*<<< orphan*/  PutSegmentHeader (TYPE_3__* const,TYPE_2__* const) ; 
 int /*<<< orphan*/  VP8BitWriterFinish (TYPE_3__* const) ; 
 int /*<<< orphan*/  VP8BitWriterInit (TYPE_3__* const,int const) ; 
 int VP8BitWriterPos (TYPE_3__* const) ; 
 int /*<<< orphan*/  VP8CodeIntraModes (TYPE_2__* const) ; 
 int /*<<< orphan*/  VP8PutBitUniform (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8PutBits (TYPE_3__* const,int,int) ; 
 int /*<<< orphan*/  VP8WriteProbas (TYPE_3__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 int WebPEncodingSetError (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int GeneratePartition0(VP8Encoder* const enc) {
  VP8BitWriter* const bw = &enc->bw_;
  const int mb_size = enc->mb_w_ * enc->mb_h_;
  uint64_t pos1, pos2, pos3;

  pos1 = VP8BitWriterPos(bw);
  if (!VP8BitWriterInit(bw, mb_size * 7 / 8)) {        // ~7 bits per macroblock
    return WebPEncodingSetError(enc->pic_, VP8_ENC_ERROR_OUT_OF_MEMORY);
  }
  VP8PutBitUniform(bw, 0);   // colorspace
  VP8PutBitUniform(bw, 0);   // clamp type

  PutSegmentHeader(bw, enc);
  PutFilterHeader(bw, &enc->filter_hdr_);
  VP8PutBits(bw, enc->num_parts_ == 8 ? 3 :
                 enc->num_parts_ == 4 ? 2 :
                 enc->num_parts_ == 2 ? 1 : 0, 2);
  PutQuant(bw, enc);
  VP8PutBitUniform(bw, 0);   // no proba update
  VP8WriteProbas(bw, &enc->proba_);
  pos2 = VP8BitWriterPos(bw);
  VP8CodeIntraModes(enc);
  VP8BitWriterFinish(bw);

  pos3 = VP8BitWriterPos(bw);

#if !defined(WEBP_DISABLE_STATS)
  if (enc->pic_->stats) {
    enc->pic_->stats->header_bytes[0] = (int)((pos2 - pos1 + 7) >> 3);
    enc->pic_->stats->header_bytes[1] = (int)((pos3 - pos2 + 7) >> 3);
    enc->pic_->stats->alpha_data_size = (int)enc->alpha_data_size_;
  }
#else
  (void)pos1;
  (void)pos2;
  (void)pos3;
#endif
  if (bw->error_) {
    return WebPEncodingSetError(enc->pic_, VP8_ENC_ERROR_OUT_OF_MEMORY);
  }
  return 1;
}