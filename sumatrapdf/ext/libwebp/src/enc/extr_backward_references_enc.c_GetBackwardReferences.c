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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  hash_chain_box ;
typedef  int /*<<< orphan*/  VP8LHistogram ;
typedef  int /*<<< orphan*/  const VP8LHashChain ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;

/* Variables and functions */
 int /*<<< orphan*/  BackwardReferences2DLocality (int,int /*<<< orphan*/ *) ; 
 int BackwardReferencesLz77 (int,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 int BackwardReferencesLz77Box (int,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BackwardReferencesRle (int,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BackwardRefsWithLocalCache (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CalculateBestCacheSize (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MAX_COLOR_CACHE_BITS ; 
 int /*<<< orphan*/ * VP8LAllocateHistogram (int /*<<< orphan*/ ) ; 
 scalar_t__ VP8LBackwardReferencesTraceBackwards (int,int,int /*<<< orphan*/  const* const,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LFreeHistogram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LHashChainClear (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VP8LHashChainInit (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  VP8LHistogramCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 double VP8LHistogramEstimateBits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
#define  kLZ77Box 130 
#define  kLZ77RLE 129 
#define  kLZ77Standard 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VP8LBackwardRefs* GetBackwardReferences(
    int width, int height, const uint32_t* const argb, int quality,
    int lz77_types_to_try, int* const cache_bits,
    const VP8LHashChain* const hash_chain, VP8LBackwardRefs* best,
    VP8LBackwardRefs* worst) {
  const int cache_bits_initial = *cache_bits;
  double bit_cost_best = -1;
  VP8LHistogram* histo = NULL;
  int lz77_type, lz77_type_best = 0;
  VP8LHashChain hash_chain_box;
  memset(&hash_chain_box, 0, sizeof(hash_chain_box));

  histo = VP8LAllocateHistogram(MAX_COLOR_CACHE_BITS);
  if (histo == NULL) goto Error;

  for (lz77_type = 1; lz77_types_to_try;
       lz77_types_to_try &= ~lz77_type, lz77_type <<= 1) {
    int res = 0;
    double bit_cost;
    int cache_bits_tmp = cache_bits_initial;
    if ((lz77_types_to_try & lz77_type) == 0) continue;
    switch (lz77_type) {
      case kLZ77RLE:
        res = BackwardReferencesRle(width, height, argb, 0, worst);
        break;
      case kLZ77Standard:
        // Compute LZ77 with no cache (0 bits), as the ideal LZ77 with a color
        // cache is not that different in practice.
        res = BackwardReferencesLz77(width, height, argb, 0, hash_chain, worst);
        break;
      case kLZ77Box:
        if (!VP8LHashChainInit(&hash_chain_box, width * height)) goto Error;
        res = BackwardReferencesLz77Box(width, height, argb, 0, hash_chain,
                                        &hash_chain_box, worst);
        break;
      default:
        assert(0);
    }
    if (!res) goto Error;

    // Next, try with a color cache and update the references.
    if (!CalculateBestCacheSize(argb, quality, worst, &cache_bits_tmp)) {
      goto Error;
    }
    if (cache_bits_tmp > 0) {
      if (!BackwardRefsWithLocalCache(argb, cache_bits_tmp, worst)) {
        goto Error;
      }
    }

    // Keep the best backward references.
    VP8LHistogramCreate(histo, worst, cache_bits_tmp);
    bit_cost = VP8LHistogramEstimateBits(histo);
    if (lz77_type_best == 0 || bit_cost < bit_cost_best) {
      VP8LBackwardRefs* const tmp = worst;
      worst = best;
      best = tmp;
      bit_cost_best = bit_cost;
      *cache_bits = cache_bits_tmp;
      lz77_type_best = lz77_type;
    }
  }
  assert(lz77_type_best > 0);

  // Improve on simple LZ77 but only for high quality (TraceBackwards is
  // costly).
  if ((lz77_type_best == kLZ77Standard || lz77_type_best == kLZ77Box) &&
      quality >= 25) {
    const VP8LHashChain* const hash_chain_tmp =
        (lz77_type_best == kLZ77Standard) ? hash_chain : &hash_chain_box;
    if (VP8LBackwardReferencesTraceBackwards(width, height, argb, *cache_bits,
                                             hash_chain_tmp, best, worst)) {
      double bit_cost_trace;
      VP8LHistogramCreate(histo, worst, *cache_bits);
      bit_cost_trace = VP8LHistogramEstimateBits(histo);
      if (bit_cost_trace < bit_cost_best) best = worst;
    }
  }

  BackwardReferences2DLocality(width, best);

Error:
  VP8LHashChainClear(&hash_chain_box);
  VP8LFreeHistogram(histo);
  return best;
}