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
struct TYPE_7__ {int level_; int sharpness_; scalar_t__* mode_lf_delta_; scalar_t__* ref_lf_delta_; scalar_t__ use_lf_delta_; } ;
typedef  TYPE_2__ VP8FilterHeader ;
struct TYPE_8__ {int f_ilevel_; int f_limit_; int hev_thresh_; int f_inner_; } ;
typedef  TYPE_3__ VP8FInfo ;
struct TYPE_6__ {int* filter_strength_; int /*<<< orphan*/  absolute_delta_; scalar_t__ use_segment_; } ;
struct TYPE_9__ {scalar_t__ filter_type_; TYPE_3__** fstrengths_; TYPE_1__ segment_hdr_; TYPE_2__ filter_hdr_; } ;
typedef  TYPE_4__ VP8Decoder ;

/* Variables and functions */
 int NUM_MB_SEGMENTS ; 

__attribute__((used)) static void PrecomputeFilterStrengths(VP8Decoder* const dec) {
  if (dec->filter_type_ > 0) {
    int s;
    const VP8FilterHeader* const hdr = &dec->filter_hdr_;
    for (s = 0; s < NUM_MB_SEGMENTS; ++s) {
      int i4x4;
      // First, compute the initial level
      int base_level;
      if (dec->segment_hdr_.use_segment_) {
        base_level = dec->segment_hdr_.filter_strength_[s];
        if (!dec->segment_hdr_.absolute_delta_) {
          base_level += hdr->level_;
        }
      } else {
        base_level = hdr->level_;
      }
      for (i4x4 = 0; i4x4 <= 1; ++i4x4) {
        VP8FInfo* const info = &dec->fstrengths_[s][i4x4];
        int level = base_level;
        if (hdr->use_lf_delta_) {
          level += hdr->ref_lf_delta_[0];
          if (i4x4) {
            level += hdr->mode_lf_delta_[0];
          }
        }
        level = (level < 0) ? 0 : (level > 63) ? 63 : level;
        if (level > 0) {
          int ilevel = level;
          if (hdr->sharpness_ > 0) {
            if (hdr->sharpness_ > 4) {
              ilevel >>= 2;
            } else {
              ilevel >>= 1;
            }
            if (ilevel > 9 - hdr->sharpness_) {
              ilevel = 9 - hdr->sharpness_;
            }
          }
          if (ilevel < 1) ilevel = 1;
          info->f_ilevel_ = ilevel;
          info->f_limit_ = 2 * level + ilevel;
          info->hev_thresh_ = (level >= 40) ? 2 : (level >= 15) ? 1 : 0;
        } else {
          info->f_limit_ = 0;  // no filtering
        }
        info->f_inner_ = i4x4;
      }
    }
  }
}