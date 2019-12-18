#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int palette_code_bits_; int trivial_symbol_; scalar_t__ distance_; int /*<<< orphan*/ * is_used_; scalar_t__ alpha_; scalar_t__ blue_; scalar_t__ red_; scalar_t__ literal_; } ;
typedef  TYPE_1__ VP8LHistogram ;

/* Variables and functions */
 scalar_t__ GetCombinedEntropy (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NUM_DISTANCE_CODES ; 
 scalar_t__ NUM_LENGTH_CODES ; 
 scalar_t__ NUM_LITERAL_CODES ; 
 scalar_t__ VP8LExtraCostCombined (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ VP8LHistogramNumCodes (int const) ; 
 int VP8L_NON_TRIVIAL_SYM ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int GetCombinedHistogramEntropy(const VP8LHistogram* const a,
                                       const VP8LHistogram* const b,
                                       double cost_threshold,
                                       double* cost) {
  const int palette_code_bits = a->palette_code_bits_;
  int trivial_at_end = 0;
  assert(a->palette_code_bits_ == b->palette_code_bits_);
  *cost += GetCombinedEntropy(a->literal_, b->literal_,
                              VP8LHistogramNumCodes(palette_code_bits),
                              a->is_used_[0], b->is_used_[0], 0);
  *cost += VP8LExtraCostCombined(a->literal_ + NUM_LITERAL_CODES,
                                 b->literal_ + NUM_LITERAL_CODES,
                                 NUM_LENGTH_CODES);
  if (*cost > cost_threshold) return 0;

  if (a->trivial_symbol_ != VP8L_NON_TRIVIAL_SYM &&
      a->trivial_symbol_ == b->trivial_symbol_) {
    // A, R and B are all 0 or 0xff.
    const uint32_t color_a = (a->trivial_symbol_ >> 24) & 0xff;
    const uint32_t color_r = (a->trivial_symbol_ >> 16) & 0xff;
    const uint32_t color_b = (a->trivial_symbol_ >> 0) & 0xff;
    if ((color_a == 0 || color_a == 0xff) &&
        (color_r == 0 || color_r == 0xff) &&
        (color_b == 0 || color_b == 0xff)) {
      trivial_at_end = 1;
    }
  }

  *cost +=
      GetCombinedEntropy(a->red_, b->red_, NUM_LITERAL_CODES, a->is_used_[1],
                         b->is_used_[1], trivial_at_end);
  if (*cost > cost_threshold) return 0;

  *cost +=
      GetCombinedEntropy(a->blue_, b->blue_, NUM_LITERAL_CODES, a->is_used_[2],
                         b->is_used_[2], trivial_at_end);
  if (*cost > cost_threshold) return 0;

  *cost +=
      GetCombinedEntropy(a->alpha_, b->alpha_, NUM_LITERAL_CODES,
                         a->is_used_[3], b->is_used_[3], trivial_at_end);
  if (*cost > cost_threshold) return 0;

  *cost +=
      GetCombinedEntropy(a->distance_, b->distance_, NUM_DISTANCE_CODES,
                         a->is_used_[4], b->is_used_[4], 0);
  *cost +=
      VP8LExtraCostCombined(a->distance_, b->distance_, NUM_DISTANCE_CODES);
  if (*cost > cost_threshold) return 0;

  return 1;
}