#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double bit_cost_; } ;
typedef  TYPE_1__ VP8LHistogram ;
struct TYPE_9__ {int cost_combo; int /*<<< orphan*/  cost_diff; } ;
typedef  TYPE_2__ HistogramPair ;

/* Variables and functions */
 int /*<<< orphan*/  GetCombinedHistogramEntropy (TYPE_1__ const* const,TYPE_1__ const* const,double const,int*) ; 

__attribute__((used)) static void HistoQueueUpdatePair(const VP8LHistogram* const h1,
                                 const VP8LHistogram* const h2,
                                 double threshold,
                                 HistogramPair* const pair) {
  const double sum_cost = h1->bit_cost_ + h2->bit_cost_;
  pair->cost_combo = 0.;
  GetCombinedHistogramEntropy(h1, h2, sum_cost + threshold, &pair->cost_combo);
  pair->cost_diff = pair->cost_combo - sum_cost;
}