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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int max_size; int size; TYPE_2__** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;
struct TYPE_6__ {int palette_code_bits_; } ;
typedef  TYPE_2__ VP8LHistogram ;

/* Variables and functions */
 int /*<<< orphan*/  HistogramSetResetPointers (TYPE_1__* const,int const) ; 
 size_t HistogramSetTotalSize (int const,int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 

void VP8LHistogramSetClear(VP8LHistogramSet* const set) {
  int i;
  const int cache_bits = set->histograms[0]->palette_code_bits_;
  const int size = set->max_size;
  const size_t total_size = HistogramSetTotalSize(size, cache_bits);
  uint8_t* memory = (uint8_t*)set;

  memset(memory, 0, total_size);
  memory += sizeof(*set);
  set->histograms = (VP8LHistogram**)memory;
  set->max_size = size;
  set->size = size;
  HistogramSetResetPointers(set, cache_bits);
  for (i = 0; i < size; ++i) {
    set->histograms[i]->palette_code_bits_ = cache_bits;
  }
}