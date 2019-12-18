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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ VP8AccumulateSSE (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static double AccumulateSSE(const uint8_t* src, int src_stride,
                            const uint8_t* ref, int ref_stride,
                            int w, int h) {
  int y;
  double total_sse = 0.;
  for (y = 0; y < h; ++y) {
    total_sse += VP8AccumulateSSE(src, ref, w);
    src += src_stride;
    ref += ref_stride;
  }
  return total_sse;
}