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
typedef  int /*<<< orphan*/  VP8LHashChain ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;

/* Variables and functions */
 int /*<<< orphan*/ * GetBackwardReferences (int,int,int /*<<< orphan*/  const* const,int,int,int* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * GetBackwardReferencesLowEffort (int,int,int /*<<< orphan*/  const* const,int* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const) ; 

VP8LBackwardRefs* VP8LGetBackwardReferences(
    int width, int height, const uint32_t* const argb, int quality,
    int low_effort, int lz77_types_to_try, int* const cache_bits,
    const VP8LHashChain* const hash_chain, VP8LBackwardRefs* const refs_tmp1,
    VP8LBackwardRefs* const refs_tmp2) {
  if (low_effort) {
    return GetBackwardReferencesLowEffort(width, height, argb, cache_bits,
                                          hash_chain, refs_tmp1);
  } else {
    return GetBackwardReferences(width, height, argb, quality,
                                 lz77_types_to_try, cache_bits, hash_chain,
                                 refs_tmp1, refs_tmp2);
  }
}