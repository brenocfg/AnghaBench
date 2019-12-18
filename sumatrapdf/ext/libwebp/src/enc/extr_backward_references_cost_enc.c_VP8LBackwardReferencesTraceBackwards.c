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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  VP8LHashChain ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;

/* Variables and functions */
 int /*<<< orphan*/  BackwardReferencesHashChainDistanceOnly (int,int,int /*<<< orphan*/  const* const,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BackwardReferencesHashChainFollowChosenPath (int /*<<< orphan*/  const* const,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  TraceBackwards (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPSafeMalloc (int const,int) ; 

int VP8LBackwardReferencesTraceBackwards(int xsize, int ysize,
                                         const uint32_t* const argb,
                                         int cache_bits,
                                         const VP8LHashChain* const hash_chain,
                                         const VP8LBackwardRefs* const refs_src,
                                         VP8LBackwardRefs* const refs_dst) {
  int ok = 0;
  const int dist_array_size = xsize * ysize;
  uint16_t* chosen_path = NULL;
  int chosen_path_size = 0;
  uint16_t* dist_array =
      (uint16_t*)WebPSafeMalloc(dist_array_size, sizeof(*dist_array));

  if (dist_array == NULL) goto Error;

  if (!BackwardReferencesHashChainDistanceOnly(
          xsize, ysize, argb, cache_bits, hash_chain, refs_src, dist_array)) {
    goto Error;
  }
  TraceBackwards(dist_array, dist_array_size, &chosen_path, &chosen_path_size);
  if (!BackwardReferencesHashChainFollowChosenPath(
          argb, cache_bits, chosen_path, chosen_path_size, hash_chain,
          refs_dst)) {
    goto Error;
  }
  ok = 1;
 Error:
  WebPSafeFree(dist_array);
  return ok;
}