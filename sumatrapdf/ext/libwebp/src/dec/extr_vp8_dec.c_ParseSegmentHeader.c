#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* update_map_; void** filter_strength_; void** quantizer_; void* absolute_delta_; void* use_segment_; } ;
typedef  TYPE_1__ VP8SegmentHeader ;
struct TYPE_11__ {unsigned int* segments_; } ;
typedef  TYPE_2__ VP8Proba ;
struct TYPE_12__ {int /*<<< orphan*/  eof_; } ;
typedef  TYPE_3__ VP8BitReader ;

/* Variables and functions */
 int MB_FEATURE_TREE_PROBS ; 
 int NUM_MB_SEGMENTS ; 
 void* VP8Get (TYPE_3__*,char*) ; 
 void* VP8GetSignedValue (TYPE_3__*,int,char*) ; 
 unsigned int VP8GetValue (TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ParseSegmentHeader(VP8BitReader* br,
                              VP8SegmentHeader* hdr, VP8Proba* proba) {
  assert(br != NULL);
  assert(hdr != NULL);
  hdr->use_segment_ = VP8Get(br, "global-header");
  if (hdr->use_segment_) {
    hdr->update_map_ = VP8Get(br, "global-header");
    if (VP8Get(br, "global-header")) {   // update data
      int s;
      hdr->absolute_delta_ = VP8Get(br, "global-header");
      for (s = 0; s < NUM_MB_SEGMENTS; ++s) {
        hdr->quantizer_[s] = VP8Get(br, "global-header") ?
            VP8GetSignedValue(br, 7, "global-header") : 0;
      }
      for (s = 0; s < NUM_MB_SEGMENTS; ++s) {
        hdr->filter_strength_[s] = VP8Get(br, "global-header") ?
            VP8GetSignedValue(br, 6, "global-header") : 0;
      }
    }
    if (hdr->update_map_) {
      int s;
      for (s = 0; s < MB_FEATURE_TREE_PROBS; ++s) {
        proba->segments_[s] = VP8Get(br, "global-header") ?
            VP8GetValue(br, 8, "global-header") : 255u;
      }
    }
  } else {
    hdr->update_map_ = 0;
  }
  return !br->eof_;
}