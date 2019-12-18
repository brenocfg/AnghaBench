#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__** streaks; } ;
typedef  TYPE_1__ VP8LStreaks ;
struct TYPE_8__ {int nonzeros; int /*<<< orphan*/  nonzero_code; } ;
typedef  TYPE_2__ VP8LBitEntropy ;

/* Variables and functions */
 double BitsEntropyRefine (TYPE_2__*) ; 
 double FinalHuffmanCost (TYPE_1__*) ; 
 int /*<<< orphan*/  VP8LGetEntropyUnrefined (int /*<<< orphan*/  const* const,int,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  VP8L_NON_TRIVIAL_SYM ; 

__attribute__((used)) static double PopulationCost(const uint32_t* const population, int length,
                             uint32_t* const trivial_sym,
                             uint8_t* const is_used) {
  VP8LBitEntropy bit_entropy;
  VP8LStreaks stats;
  VP8LGetEntropyUnrefined(population, length, &bit_entropy, &stats);
  if (trivial_sym != NULL) {
    *trivial_sym = (bit_entropy.nonzeros == 1) ? bit_entropy.nonzero_code
                                               : VP8L_NON_TRIVIAL_SYM;
  }
  // The histogram is used if there is at least one non-zero streak.
  *is_used = (stats.streaks[1][0] != 0 || stats.streaks[1][1] != 0);

  return BitsEntropyRefine(&bit_entropy) + FinalHuffmanCost(&stats);
}