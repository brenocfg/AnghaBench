#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  map_tmp ;
typedef  int /*<<< orphan*/  VP8LHistogramSet ;
typedef  int /*<<< orphan*/  VP8LHistogram ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;

/* Variables and functions */
 int BIN_SIZE ; 
 double GetCombineCostFactor (int const,int) ; 
 int /*<<< orphan*/  HistogramAnalyzeEntropyBin (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  HistogramBuild (int,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  HistogramCombineEntropyBin (int /*<<< orphan*/ * const,int*,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int const,double const,int) ; 
 int /*<<< orphan*/  HistogramCombineGreedy (int /*<<< orphan*/ * const,int*) ; 
 int /*<<< orphan*/  HistogramCombineStochastic (int /*<<< orphan*/ * const,int*,int const,int*) ; 
 int /*<<< orphan*/  HistogramCopyAndAnalyze (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int*,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  HistogramRemap (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int MAX_HISTO_GREEDY ; 
 int NUM_PARTITIONS ; 
 int /*<<< orphan*/  OptimizeHistogramSymbols (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  RemoveEmptyHistograms (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * VP8LAllocateHistogramSet (int const,int) ; 
 int /*<<< orphan*/  VP8LFreeHistogramSet (int /*<<< orphan*/ * const) ; 
 int VP8LSubSampleSize (int,int) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * WebPSafeMalloc (int,int) ; 

int VP8LGetHistoImageSymbols(int xsize, int ysize,
                             const VP8LBackwardRefs* const refs,
                             int quality, int low_effort,
                             int histo_bits, int cache_bits,
                             VP8LHistogramSet* const image_histo,
                             VP8LHistogram* const tmp_histo,
                             uint16_t* const histogram_symbols) {
  int ok = 0;
  const int histo_xsize = histo_bits ? VP8LSubSampleSize(xsize, histo_bits) : 1;
  const int histo_ysize = histo_bits ? VP8LSubSampleSize(ysize, histo_bits) : 1;
  const int image_histo_raw_size = histo_xsize * histo_ysize;
  VP8LHistogramSet* const orig_histo =
      VP8LAllocateHistogramSet(image_histo_raw_size, cache_bits);
  // Don't attempt linear bin-partition heuristic for
  // histograms of small sizes (as bin_map will be very sparse) and
  // maximum quality q==100 (to preserve the compression gains at that level).
  const int entropy_combine_num_bins = low_effort ? NUM_PARTITIONS : BIN_SIZE;
  int entropy_combine;
  uint16_t* const map_tmp =
      WebPSafeMalloc(2 * image_histo_raw_size, sizeof(map_tmp));
  uint16_t* const cluster_mappings = map_tmp + image_histo_raw_size;
  int num_used = image_histo_raw_size;
  if (orig_histo == NULL || map_tmp == NULL) goto Error;

  // Construct the histograms from backward references.
  HistogramBuild(xsize, histo_bits, refs, orig_histo);
  // Copies the histograms and computes its bit_cost.
  // histogram_symbols is optimized
  HistogramCopyAndAnalyze(orig_histo, image_histo, &num_used,
                          histogram_symbols);

  entropy_combine =
      (num_used > entropy_combine_num_bins * 2) && (quality < 100);

  if (entropy_combine) {
    uint16_t* const bin_map = map_tmp;
    const double combine_cost_factor =
        GetCombineCostFactor(image_histo_raw_size, quality);
    const uint32_t num_clusters = num_used;

    HistogramAnalyzeEntropyBin(image_histo, bin_map, low_effort);
    // Collapse histograms with similar entropy.
    HistogramCombineEntropyBin(image_histo, &num_used, histogram_symbols,
                               cluster_mappings, tmp_histo, bin_map,
                               entropy_combine_num_bins, combine_cost_factor,
                               low_effort);
    OptimizeHistogramSymbols(image_histo, cluster_mappings, num_clusters,
                             map_tmp, histogram_symbols);
  }

  // Don't combine the histograms using stochastic and greedy heuristics for
  // low-effort compression mode.
  if (!low_effort || !entropy_combine) {
    const float x = quality / 100.f;
    // cubic ramp between 1 and MAX_HISTO_GREEDY:
    const int threshold_size = (int)(1 + (x * x * x) * (MAX_HISTO_GREEDY - 1));
    int do_greedy;
    if (!HistogramCombineStochastic(image_histo, &num_used, threshold_size,
                                    &do_greedy)) {
      goto Error;
    }
    if (do_greedy) {
      RemoveEmptyHistograms(image_histo);
      if (!HistogramCombineGreedy(image_histo, &num_used)) {
        goto Error;
      }
    }
  }

  // Find the optimal map from original histograms to the final ones.
  RemoveEmptyHistograms(image_histo);
  HistogramRemap(orig_histo, image_histo, histogram_symbols);

  ok = 1;

 Error:
  VP8LFreeHistogramSet(orig_histo);
  WebPSafeFree(map_tmp);
  return ok;
}