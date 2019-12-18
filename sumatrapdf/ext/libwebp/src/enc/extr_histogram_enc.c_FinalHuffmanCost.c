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
struct TYPE_3__ {double* counts; double** streaks; } ;
typedef  TYPE_1__ VP8LStreaks ;

/* Variables and functions */
 double InitialHuffmanCost () ; 

__attribute__((used)) static double FinalHuffmanCost(const VP8LStreaks* const stats) {
  // The constants in this function are experimental and got rounded from
  // their original values in 1/8 when switched to 1/1024.
  double retval = InitialHuffmanCost();
  // Second coefficient: Many zeros in the histogram are covered efficiently
  // by a run-length encode. Originally 2/8.
  retval += stats->counts[0] * 1.5625 + 0.234375 * stats->streaks[0][1];
  // Second coefficient: Constant values are encoded less efficiently, but still
  // RLE'ed. Originally 6/8.
  retval += stats->counts[1] * 2.578125 + 0.703125 * stats->streaks[1][1];
  // 0s are usually encoded more efficiently than non-0s.
  // Originally 15/8.
  retval += 1.796875 * stats->streaks[0][0];
  // Originally 26/8.
  retval += 3.28125 * stats->streaks[1][0];
  return retval;
}