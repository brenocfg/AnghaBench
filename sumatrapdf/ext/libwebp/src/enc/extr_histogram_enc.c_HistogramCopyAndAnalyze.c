#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int max_size; TYPE_2__** histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;
struct TYPE_10__ {int /*<<< orphan*/ * is_used_; } ;
typedef  TYPE_2__ VP8LHistogram ;

/* Variables and functions */
 int /*<<< orphan*/  HistogramCopy (TYPE_2__* const,TYPE_2__*) ; 
 int /*<<< orphan*/  HistogramSetRemoveHistogram (TYPE_1__* const,int,int* const) ; 
 int /*<<< orphan*/  UpdateHistogramCost (TYPE_2__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kInvalidHistogramSymbol ; 

__attribute__((used)) static void HistogramCopyAndAnalyze(VP8LHistogramSet* const orig_histo,
                                    VP8LHistogramSet* const image_histo,
                                    int* const num_used,
                                    uint16_t* const histogram_symbols) {
  int i, cluster_id;
  int num_used_orig = *num_used;
  VP8LHistogram** const orig_histograms = orig_histo->histograms;
  VP8LHistogram** const histograms = image_histo->histograms;
  assert(image_histo->max_size == orig_histo->max_size);
  for (cluster_id = 0, i = 0; i < orig_histo->max_size; ++i) {
    VP8LHistogram* const histo = orig_histograms[i];
    UpdateHistogramCost(histo);

    // Skip the histogram if it is completely empty, which can happen for tiles
    // with no information (when they are skipped because of LZ77).
    if (!histo->is_used_[0] && !histo->is_used_[1] && !histo->is_used_[2]
        && !histo->is_used_[3] && !histo->is_used_[4]) {
      // The first histogram is always used. If an histogram is empty, we set
      // its id to be the same as the previous one: this will improve
      // compressibility for later LZ77.
      assert(i > 0);
      HistogramSetRemoveHistogram(image_histo, i, num_used);
      HistogramSetRemoveHistogram(orig_histo, i, &num_used_orig);
      histogram_symbols[i] = kInvalidHistogramSymbol;
    } else {
      // Copy histograms from orig_histo[] to image_histo[].
      HistogramCopy(histo, histograms[i]);
      histogram_symbols[i] = cluster_id++;
      assert(cluster_id <= image_histo->max_size);
    }
  }
}