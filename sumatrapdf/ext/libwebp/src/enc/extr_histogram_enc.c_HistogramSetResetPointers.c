#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int max_size; TYPE_2__** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;
struct TYPE_5__ {int /*<<< orphan*/ * literal_; } ;
typedef  TYPE_2__ VP8LHistogram ;

/* Variables and functions */
 int VP8LGetHistogramSize (int) ; 
 scalar_t__ WEBP_ALIGN (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HistogramSetResetPointers(VP8LHistogramSet* const set,
                                      int cache_bits) {
  int i;
  const int histo_size = VP8LGetHistogramSize(cache_bits);
  uint8_t* memory = (uint8_t*) (set->histograms);
  memory += set->max_size * sizeof(*set->histograms);
  for (i = 0; i < set->max_size; ++i) {
    memory = (uint8_t*) WEBP_ALIGN(memory);
    set->histograms[i] = (VP8LHistogram*) memory;
    // literal_ won't necessary be aligned.
    set->histograms[i]->literal_ = (uint32_t*)(memory + sizeof(VP8LHistogram));
    memory += histo_size;
  }
}