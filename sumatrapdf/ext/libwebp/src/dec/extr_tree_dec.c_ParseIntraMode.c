#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_8__ {int segment_; int skip_; int is_i4x4_; int* imodes_; void* uvmode_; } ;
typedef  TYPE_3__ VP8MBData ;
struct TYPE_7__ {int* segments_; } ;
struct TYPE_6__ {scalar_t__ update_map_; } ;
struct TYPE_9__ {size_t* intra_t_; size_t* intra_l_; int skip_p_; scalar_t__ use_skip_proba_; TYPE_2__ proba_; TYPE_1__ segment_hdr_; TYPE_3__* mb_data_; } ;
typedef  TYPE_4__ VP8Decoder ;
typedef  int /*<<< orphan*/  VP8BitReader ;

/* Variables and functions */
 int B_DC_PRED ; 
 int B_HD_PRED ; 
 int B_HE_PRED ; 
 int B_HU_PRED ; 
 int B_LD_PRED ; 
 int B_RD_PRED ; 
 int B_TM_PRED ; 
 int B_VE_PRED ; 
 int B_VL_PRED ; 
 int B_VR_PRED ; 
 void* DC_PRED ; 
 void* H_PRED ; 
 void* TM_PRED ; 
 int VP8GetBit (int /*<<< orphan*/ * const,size_t const,char*) ; 
 void* V_PRED ; 
 size_t*** kBModesProba ; 
 int* kYModesIntra4 ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t* const,int) ; 
 int /*<<< orphan*/  memset (size_t* const,int const,int) ; 

__attribute__((used)) static void ParseIntraMode(VP8BitReader* const br,
                           VP8Decoder* const dec, int mb_x) {
  uint8_t* const top = dec->intra_t_ + 4 * mb_x;
  uint8_t* const left = dec->intra_l_;
  VP8MBData* const block = dec->mb_data_ + mb_x;

  // Note: we don't save segment map (yet), as we don't expect
  // to decode more than 1 keyframe.
  if (dec->segment_hdr_.update_map_) {
    // Hardcoded tree parsing
    block->segment_ = !VP8GetBit(br, dec->proba_.segments_[0], "segments")
                    ?  VP8GetBit(br, dec->proba_.segments_[1], "segments")
                    :  VP8GetBit(br, dec->proba_.segments_[2], "segments") + 2;
  } else {
    block->segment_ = 0;  // default for intra
  }
  if (dec->use_skip_proba_) block->skip_ = VP8GetBit(br, dec->skip_p_, "skip");

  block->is_i4x4_ = !VP8GetBit(br, 145, "block-size");
  if (!block->is_i4x4_) {
    // Hardcoded 16x16 intra-mode decision tree.
    const int ymode =
        VP8GetBit(br, 156, "pred-modes") ?
            (VP8GetBit(br, 128, "pred-modes") ? TM_PRED : H_PRED) :
            (VP8GetBit(br, 163, "pred-modes") ? V_PRED : DC_PRED);
    block->imodes_[0] = ymode;
    memset(top, ymode, 4 * sizeof(*top));
    memset(left, ymode, 4 * sizeof(*left));
  } else {
    uint8_t* modes = block->imodes_;
    int y;
    for (y = 0; y < 4; ++y) {
      int ymode = left[y];
      int x;
      for (x = 0; x < 4; ++x) {
        const uint8_t* const prob = kBModesProba[top[x]][ymode];
#if (USE_GENERIC_TREE == 1)
        // Generic tree-parsing
        int i = kYModesIntra4[VP8GetBit(br, prob[0], "pred-modes")];
        while (i > 0) {
          i = kYModesIntra4[2 * i + VP8GetBit(br, prob[i], "pred-modes")];
        }
        ymode = -i;
#else
        // Hardcoded tree parsing
        ymode = !VP8GetBit(br, prob[0], "pred-modes") ? B_DC_PRED :
                  !VP8GetBit(br, prob[1], "pred-modes") ? B_TM_PRED :
                    !VP8GetBit(br, prob[2], "pred-modes") ? B_VE_PRED :
                      !VP8GetBit(br, prob[3], "pred-modes") ?
                        (!VP8GetBit(br, prob[4], "pred-modes") ? B_HE_PRED :
                          (!VP8GetBit(br, prob[5], "pred-modes") ? B_RD_PRED
                                                                 : B_VR_PRED)) :
                        (!VP8GetBit(br, prob[6], "pred-modes") ? B_LD_PRED :
                          (!VP8GetBit(br, prob[7], "pred-modes") ? B_VL_PRED :
                            (!VP8GetBit(br, prob[8], "pred-modes") ? B_HD_PRED
                                                                   : B_HU_PRED))
                        );
#endif  // USE_GENERIC_TREE
        top[x] = ymode;
      }
      memcpy(modes, top, 4 * sizeof(*top));
      modes += 4;
      left[y] = ymode;
    }
  }
  // Hardcoded UVMode decision tree
  block->uvmode_ = !VP8GetBit(br, 142, "pred-modes-uv") ? DC_PRED
                 : !VP8GetBit(br, 114, "pred-modes-uv") ? V_PRED
                 : VP8GetBit(br, 183, "pred-modes-uv") ? TM_PRED : H_PRED;
}