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
typedef  int uint32_t ;

/* Variables and functions */
 int const APPROX_LOG_MAX ; 
 int APPROX_LOG_WITH_CORRECTION_MAX ; 
 int LOG_2_RECIPROCAL ; 
 int LOG_LOOKUP_IDX_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int* kLog2Table ; 
 int log (double) ; 

__attribute__((used)) static float FastLog2Slow_C(uint32_t v) {
  assert(v >= LOG_LOOKUP_IDX_MAX);
  if (v < APPROX_LOG_WITH_CORRECTION_MAX) {
    int log_cnt = 0;
    uint32_t y = 1;
    const uint32_t orig_v = v;
    double log_2;
    do {
      ++log_cnt;
      v = v >> 1;
      y = y << 1;
    } while (v >= LOG_LOOKUP_IDX_MAX);
    log_2 = kLog2Table[v] + log_cnt;
    if (orig_v >= APPROX_LOG_MAX) {
      // Since the division is still expensive, add this correction factor only
      // for large values of 'v'.
      const int correction = (23 * (orig_v & (y - 1))) >> 4;
      log_2 += (double)correction / orig_v;
    }
    return (float)log_2;
  } else {
    return (float)(LOG_2_RECIPROCAL * log((double)v));
  }
}