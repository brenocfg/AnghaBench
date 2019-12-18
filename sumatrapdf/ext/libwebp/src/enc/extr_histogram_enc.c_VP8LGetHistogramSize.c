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
typedef  int /*<<< orphan*/  VP8LHistogram ;

/* Variables and functions */
 int VP8LHistogramNumCodes (int) ; 
 int /*<<< orphan*/  assert (int) ; 

int VP8LGetHistogramSize(int cache_bits) {
  const int literal_size = VP8LHistogramNumCodes(cache_bits);
  const size_t total_size = sizeof(VP8LHistogram) + sizeof(int) * literal_size;
  assert(total_size <= (size_t)0x7fffffff);
  return (int)total_size;
}