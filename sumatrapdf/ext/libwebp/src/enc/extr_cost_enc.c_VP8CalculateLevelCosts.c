#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int**** level_cost_; int**** remapped_costs_; scalar_t__ dirty_; int /*<<< orphan*/ **** coeffs_; } ;
typedef  TYPE_1__ VP8EncProba ;

/* Variables and functions */
 int MAX_VARIABLE_LEVEL ; 
 int NUM_BANDS ; 
 int NUM_CTX ; 
 int NUM_TYPES ; 
 int const VP8BitCost (int,int /*<<< orphan*/  const) ; 
 size_t* VP8EncBands ; 
 int const VariableLevelCost (int,int /*<<< orphan*/  const* const) ; 

void VP8CalculateLevelCosts(VP8EncProba* const proba) {
  int ctype, band, ctx;

  if (!proba->dirty_) return;  // nothing to do.

  for (ctype = 0; ctype < NUM_TYPES; ++ctype) {
    int n;
    for (band = 0; band < NUM_BANDS; ++band) {
      for (ctx = 0; ctx < NUM_CTX; ++ctx) {
        const uint8_t* const p = proba->coeffs_[ctype][band][ctx];
        uint16_t* const table = proba->level_cost_[ctype][band][ctx];
        const int cost0 = (ctx > 0) ? VP8BitCost(1, p[0]) : 0;
        const int cost_base = VP8BitCost(1, p[1]) + cost0;
        int v;
        table[0] = VP8BitCost(0, p[1]) + cost0;
        for (v = 1; v <= MAX_VARIABLE_LEVEL; ++v) {
          table[v] = cost_base + VariableLevelCost(v, p);
        }
        // Starting at level 67 and up, the variable part of the cost is
        // actually constant.
      }
    }
    for (n = 0; n < 16; ++n) {    // replicate bands. We don't need to sentinel.
      for (ctx = 0; ctx < NUM_CTX; ++ctx) {
        proba->remapped_costs_[ctype][n][ctx] =
            proba->level_cost_[ctype][VP8EncBands[n]][ctx];
      }
    }
  }
  proba->dirty_ = 0;
}