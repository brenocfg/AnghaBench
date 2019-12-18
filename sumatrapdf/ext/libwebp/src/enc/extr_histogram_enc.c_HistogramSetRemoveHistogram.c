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
struct TYPE_3__ {int size; int /*<<< orphan*/ ** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void HistogramSetRemoveHistogram(VP8LHistogramSet* const set, int i,
                                        int* const num_used) {
  assert(set->histograms[i] != NULL);
  set->histograms[i] = NULL;
  --*num_used;
  // If we remove the last valid one, shrink until the next valid one.
  if (i == set->size - 1) {
    while (set->size >= 1 && set->histograms[set->size - 1] == NULL) {
      --set->size;
    }
  }
}