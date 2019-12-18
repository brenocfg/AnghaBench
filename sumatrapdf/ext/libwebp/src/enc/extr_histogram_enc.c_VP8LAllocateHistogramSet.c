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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int max_size; int size; int /*<<< orphan*/ ** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;
typedef  int /*<<< orphan*/  VP8LHistogram ;

/* Variables and functions */
 int /*<<< orphan*/  HistogramSetResetPointers (TYPE_1__*,int) ; 
 size_t HistogramSetTotalSize (int,int) ; 
 int /*<<< orphan*/  VP8LHistogramInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WebPSafeMalloc (size_t const,int) ; 

VP8LHistogramSet* VP8LAllocateHistogramSet(int size, int cache_bits) {
  int i;
  VP8LHistogramSet* set;
  const size_t total_size = HistogramSetTotalSize(size, cache_bits);
  uint8_t* memory = (uint8_t*)WebPSafeMalloc(total_size, sizeof(*memory));
  if (memory == NULL) return NULL;

  set = (VP8LHistogramSet*)memory;
  memory += sizeof(*set);
  set->histograms = (VP8LHistogram**)memory;
  set->max_size = size;
  set->size = size;
  HistogramSetResetPointers(set, cache_bits);
  for (i = 0; i < size; ++i) {
    VP8LHistogramInit(set->histograms[i], cache_bits, /*init_arrays=*/ 0);
  }
  return set;
}