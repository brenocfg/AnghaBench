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
typedef  int /*<<< orphan*/  VP8LHistogramSet ;
typedef  int /*<<< orphan*/  VP8LHistogram ;

/* Variables and functions */
 int VP8LGetHistogramSize (int) ; 
 int WEBP_ALIGN_CST ; 

__attribute__((used)) static size_t HistogramSetTotalSize(int size, int cache_bits) {
  const int histo_size = VP8LGetHistogramSize(cache_bits);
  return (sizeof(VP8LHistogramSet) + size * (sizeof(VP8LHistogram*) +
          histo_size + WEBP_ALIGN_CST));
}