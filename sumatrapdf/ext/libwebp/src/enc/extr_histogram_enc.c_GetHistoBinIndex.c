#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  blue_cost_; int /*<<< orphan*/  red_cost_; int /*<<< orphan*/  literal_cost_; } ;
typedef  TYPE_1__ VP8LHistogram ;
struct TYPE_6__ {int /*<<< orphan*/  blue_max_; int /*<<< orphan*/  blue_min_; int /*<<< orphan*/  red_max_; int /*<<< orphan*/  red_min_; int /*<<< orphan*/  literal_max_; int /*<<< orphan*/  literal_min_; } ;
typedef  TYPE_2__ DominantCostRange ;

/* Variables and functions */
 int BIN_SIZE ; 
 int GetBinIdForEntropy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_PARTITIONS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int GetHistoBinIndex(const VP8LHistogram* const h,
                            const DominantCostRange* const c, int low_effort) {
  int bin_id = GetBinIdForEntropy(c->literal_min_, c->literal_max_,
                                  h->literal_cost_);
  assert(bin_id < NUM_PARTITIONS);
  if (!low_effort) {
    bin_id = bin_id * NUM_PARTITIONS
           + GetBinIdForEntropy(c->red_min_, c->red_max_, h->red_cost_);
    bin_id = bin_id * NUM_PARTITIONS
           + GetBinIdForEntropy(c->blue_min_, c->blue_max_, h->blue_cost_);
    assert(bin_id < BIN_SIZE);
  }
  return bin_id;
}