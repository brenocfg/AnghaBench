#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num_parts_; int** residual_bytes_; TYPE_1__* pic_; TYPE_5__* parts_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_10__ {int** bit_count_; TYPE_2__* enc_; } ;
typedef  TYPE_3__ VP8EncIterator ;
struct TYPE_11__ {int /*<<< orphan*/  error_; } ;
struct TYPE_8__ {int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 int NUM_MB_SEGMENTS ; 
 int /*<<< orphan*/  VP8AdjustFilterStrength (TYPE_3__* const) ; 
 int /*<<< orphan*/  VP8BitWriterFinish (TYPE_5__*) ; 
 int /*<<< orphan*/  VP8EncFreeBitWriters (TYPE_2__* const) ; 

__attribute__((used)) static int PostLoopFinalize(VP8EncIterator* const it, int ok) {
  VP8Encoder* const enc = it->enc_;
  if (ok) {      // Finalize the partitions, check for extra errors.
    int p;
    for (p = 0; p < enc->num_parts_; ++p) {
      VP8BitWriterFinish(enc->parts_ + p);
      ok &= !enc->parts_[p].error_;
    }
  }

  if (ok) {      // All good. Finish up.
#if !defined(WEBP_DISABLE_STATS)
    if (enc->pic_->stats != NULL) {  // finalize byte counters...
      int i, s;
      for (i = 0; i <= 2; ++i) {
        for (s = 0; s < NUM_MB_SEGMENTS; ++s) {
          enc->residual_bytes_[i][s] = (int)((it->bit_count_[s][i] + 7) >> 3);
        }
      }
    }
#endif
    VP8AdjustFilterStrength(it);     // ...and store filter stats.
  } else {
    // Something bad happened -> need to do some memory cleanup.
    VP8EncFreeBitWriters(enc);
  }
  return ok;
}