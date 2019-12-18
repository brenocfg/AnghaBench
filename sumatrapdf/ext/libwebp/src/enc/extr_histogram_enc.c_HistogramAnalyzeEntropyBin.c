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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/ ** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;
typedef  int /*<<< orphan*/  VP8LHistogram ;
typedef  int /*<<< orphan*/  DominantCostRange ;

/* Variables and functions */
 int /*<<< orphan*/  DominantCostRangeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHistoBinIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UpdateDominantCostRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HistogramAnalyzeEntropyBin(VP8LHistogramSet* const image_histo,
                                       uint16_t* const bin_map,
                                       int low_effort) {
  int i;
  VP8LHistogram** const histograms = image_histo->histograms;
  const int histo_size = image_histo->size;
  DominantCostRange cost_range;
  DominantCostRangeInit(&cost_range);

  // Analyze the dominant (literal, red and blue) entropy costs.
  for (i = 0; i < histo_size; ++i) {
    if (histograms[i] == NULL) continue;
    UpdateDominantCostRange(histograms[i], &cost_range);
  }

  // bin-hash histograms on three of the dominant (literal, red and blue)
  // symbol costs and store the resulting bin_id for each histogram.
  for (i = 0; i < histo_size; ++i) {
    // bin_map[i] is not set to a special value as its use will later be guarded
    // by another (histograms[i] == NULL).
    if (histograms[i] == NULL) continue;
    bin_map[i] = GetHistoBinIndex(histograms[i], &cost_range, low_effort);
  }
}