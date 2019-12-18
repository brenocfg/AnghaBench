#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VP8Histogram ;
struct TYPE_5__ {scalar_t__ yuv_p_; scalar_t__ yuv_in_; } ;
typedef  TYPE_1__ VP8EncIterator ;

/* Variables and functions */
 int DEFAULT_ALPHA ; 
 int GetAlpha (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_BETTER_ALPHA (int,int) ; 
 int /*<<< orphan*/  InitHistogram (int /*<<< orphan*/ *) ; 
 int MAX_UV_MODE ; 
 scalar_t__ U_OFF_ENC ; 
 int /*<<< orphan*/  VP8CollectHistogram (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8MakeChroma8Preds (TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8SetIntraUVMode (TYPE_1__* const,int) ; 
 scalar_t__* VP8UVModeOffsets ; 

__attribute__((used)) static int MBAnalyzeBestUVMode(VP8EncIterator* const it) {
  int best_alpha = DEFAULT_ALPHA;
  int smallest_alpha = 0;
  int best_mode = 0;
  const int max_mode = MAX_UV_MODE;
  int mode;

  VP8MakeChroma8Preds(it);
  for (mode = 0; mode < max_mode; ++mode) {
    VP8Histogram histo;
    int alpha;
    InitHistogram(&histo);
    VP8CollectHistogram(it->yuv_in_ + U_OFF_ENC,
                        it->yuv_p_ + VP8UVModeOffsets[mode],
                        16, 16 + 4 + 4, &histo);
    alpha = GetAlpha(&histo);
    if (IS_BETTER_ALPHA(alpha, best_alpha)) {
      best_alpha = alpha;
    }
    // The best prediction mode tends to be the one with the smallest alpha.
    if (mode == 0 || alpha < smallest_alpha) {
      smallest_alpha = alpha;
      best_mode = mode;
    }
  }
  VP8SetIntraUVMode(it, best_mode);
  return best_alpha;
}