#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double bit_cost_; } ;
typedef  TYPE_1__ VP8LHistogram ;

/* Variables and functions */
 int /*<<< orphan*/  GetCombinedHistogramEntropy (TYPE_1__ const* const,TYPE_1__ const* const,double,double*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static double HistogramAddThresh(const VP8LHistogram* const a,
                                 const VP8LHistogram* const b,
                                 double cost_threshold) {
  double cost;
  assert(a != NULL && b != NULL);
  cost = -a->bit_cost_;
  GetCombinedHistogramEntropy(a, b, cost_threshold, &cost);
  return cost;
}