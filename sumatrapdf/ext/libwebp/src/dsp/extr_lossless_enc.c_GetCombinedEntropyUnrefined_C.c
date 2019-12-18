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
typedef  scalar_t__ const uint32_t ;
typedef  int /*<<< orphan*/  VP8LStreaks ;
struct TYPE_5__ {int /*<<< orphan*/  sum; int /*<<< orphan*/  entropy; } ;
typedef  TYPE_1__ VP8LBitEntropy ;

/* Variables and functions */
 int /*<<< orphan*/  GetEntropyUnrefinedHelper (scalar_t__ const,int,scalar_t__ const*,int*,TYPE_1__* const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8LBitEntropyInit (TYPE_1__* const) ; 
 scalar_t__ VP8LFastSLog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void GetCombinedEntropyUnrefined_C(const uint32_t X[],
                                          const uint32_t Y[],
                                          int length,
                                          VP8LBitEntropy* const bit_entropy,
                                          VP8LStreaks* const stats) {
  int i = 1;
  int i_prev = 0;
  uint32_t xy_prev = X[0] + Y[0];

  memset(stats, 0, sizeof(*stats));
  VP8LBitEntropyInit(bit_entropy);

  for (i = 1; i < length; ++i) {
    const uint32_t xy = X[i] + Y[i];
    if (xy != xy_prev) {
      GetEntropyUnrefinedHelper(xy, i, &xy_prev, &i_prev, bit_entropy, stats);
    }
  }
  GetEntropyUnrefinedHelper(0, i, &xy_prev, &i_prev, bit_entropy, stats);

  bit_entropy->entropy += VP8LFastSLog2(bit_entropy->sum);
}