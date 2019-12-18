#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  VP8LHashChain ;
typedef  int /*<<< orphan*/  VP8LColorCache ;
struct TYPE_5__ {int /*<<< orphan*/  error_; } ;
typedef  TYPE_1__ VP8LBackwardRefs ;
typedef  int /*<<< orphan*/  PixOrCopy ;

/* Variables and functions */
 int /*<<< orphan*/  PixOrCopyCreateCacheIdx (int const) ; 
 int /*<<< orphan*/  PixOrCopyCreateCopy (int const,int const) ; 
 int /*<<< orphan*/  PixOrCopyCreateLiteral (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  VP8LBackwardRefsCursorAdd (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8LClearBackwardRefs (TYPE_1__* const) ; 
 int /*<<< orphan*/  VP8LColorCacheClear (int /*<<< orphan*/ *) ; 
 int VP8LColorCacheContains (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int VP8LColorCacheInit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8LColorCacheInsert (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int VP8LHashChainFindOffset (int /*<<< orphan*/  const* const,int) ; 

__attribute__((used)) static int BackwardReferencesHashChainFollowChosenPath(
    const uint32_t* const argb, int cache_bits,
    const uint16_t* const chosen_path, int chosen_path_size,
    const VP8LHashChain* const hash_chain, VP8LBackwardRefs* const refs) {
  const int use_color_cache = (cache_bits > 0);
  int ix;
  int i = 0;
  int ok = 0;
  int cc_init = 0;
  VP8LColorCache hashers;

  if (use_color_cache) {
    cc_init = VP8LColorCacheInit(&hashers, cache_bits);
    if (!cc_init) goto Error;
  }

  VP8LClearBackwardRefs(refs);
  for (ix = 0; ix < chosen_path_size; ++ix) {
    const int len = chosen_path[ix];
    if (len != 1) {
      int k;
      const int offset = VP8LHashChainFindOffset(hash_chain, i);
      VP8LBackwardRefsCursorAdd(refs, PixOrCopyCreateCopy(offset, len));
      if (use_color_cache) {
        for (k = 0; k < len; ++k) {
          VP8LColorCacheInsert(&hashers, argb[i + k]);
        }
      }
      i += len;
    } else {
      PixOrCopy v;
      const int idx =
          use_color_cache ? VP8LColorCacheContains(&hashers, argb[i]) : -1;
      if (idx >= 0) {
        // use_color_cache is true and hashers contains argb[i]
        // push pixel as a color cache index
        v = PixOrCopyCreateCacheIdx(idx);
      } else {
        if (use_color_cache) VP8LColorCacheInsert(&hashers, argb[i]);
        v = PixOrCopyCreateLiteral(argb[i]);
      }
      VP8LBackwardRefsCursorAdd(refs, v);
      ++i;
    }
  }
  ok = !refs->error_;
 Error:
  if (cc_init) VP8LColorCacheClear(&hashers);
  return ok;
}