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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 double const VP8LFastLog2 (scalar_t__ const) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ConvertPopulationCountTableToBitEstimates(
    int num_symbols, const uint32_t population_counts[], double output[]) {
  uint32_t sum = 0;
  int nonzeros = 0;
  int i;
  for (i = 0; i < num_symbols; ++i) {
    sum += population_counts[i];
    if (population_counts[i] > 0) {
      ++nonzeros;
    }
  }
  if (nonzeros <= 1) {
    memset(output, 0, num_symbols * sizeof(*output));
  } else {
    const double logsum = VP8LFastLog2(sum);
    for (i = 0; i < num_symbols; ++i) {
      output[i] = logsum - VP8LFastLog2(population_counts[i]);
    }
  }
}