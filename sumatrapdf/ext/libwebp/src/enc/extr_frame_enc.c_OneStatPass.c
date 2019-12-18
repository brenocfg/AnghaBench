#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  VP8RDLevel ;
struct TYPE_15__ {scalar_t__ D; scalar_t__ H; scalar_t__ R; } ;
typedef  TYPE_2__ VP8ModeScore ;
struct TYPE_13__ {int /*<<< orphan*/  nb_skip_; } ;
struct TYPE_14__ {scalar_t__ size_; } ;
struct TYPE_16__ {TYPE_11__ proba_; TYPE_1__ segment_hdr_; } ;
typedef  TYPE_3__ VP8Encoder ;
typedef  int /*<<< orphan*/  VP8EncIterator ;
struct TYPE_17__ {double value; scalar_t__ do_size_search; int /*<<< orphan*/  q; } ;
typedef  TYPE_4__ PassStats ;

/* Variables and functions */
 scalar_t__ FinalizeSkipProba (TYPE_3__* const) ; 
 scalar_t__ FinalizeTokenProbas (TYPE_11__*) ; 
 double GetPSNR (int,int const) ; 
 int HEADER_SIZE_ESTIMATE ; 
 int /*<<< orphan*/  RecordResiduals (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SetLoopParams (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 scalar_t__ VP8Decimate (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8IteratorImport (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8IteratorInit (TYPE_3__* const,int /*<<< orphan*/ *) ; 
 scalar_t__ VP8IteratorNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8IteratorProgress (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8IteratorSaveBoundary (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t OneStatPass(VP8Encoder* const enc, VP8RDLevel rd_opt,
                            int nb_mbs, int percent_delta,
                            PassStats* const s) {
  VP8EncIterator it;
  uint64_t size = 0;
  uint64_t size_p0 = 0;
  uint64_t distortion = 0;
  const uint64_t pixel_count = nb_mbs * 384;

  VP8IteratorInit(enc, &it);
  SetLoopParams(enc, s->q);
  do {
    VP8ModeScore info;
    VP8IteratorImport(&it, NULL);
    if (VP8Decimate(&it, &info, rd_opt)) {
      // Just record the number of skips and act like skip_proba is not used.
      ++enc->proba_.nb_skip_;
    }
    RecordResiduals(&it, &info);
    size += info.R + info.H;
    size_p0 += info.H;
    distortion += info.D;
    if (percent_delta && !VP8IteratorProgress(&it, percent_delta)) {
      return 0;
    }
    VP8IteratorSaveBoundary(&it);
  } while (VP8IteratorNext(&it) && --nb_mbs > 0);

  size_p0 += enc->segment_hdr_.size_;
  if (s->do_size_search) {
    size += FinalizeSkipProba(enc);
    size += FinalizeTokenProbas(&enc->proba_);
    size = ((size + size_p0 + 1024) >> 11) + HEADER_SIZE_ESTIMATE;
    s->value = (double)size;
  } else {
    s->value = GetPSNR(distortion, pixel_count);
  }
  return size_p0;
}