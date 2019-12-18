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
typedef  int const uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint8_t BlendChannelNonPremult(uint32_t src, uint8_t src_a,
                                      uint32_t dst, uint8_t dst_a,
                                      uint32_t scale, int shift) {
  const uint8_t src_channel = (src >> shift) & 0xff;
  const uint8_t dst_channel = (dst >> shift) & 0xff;
  const uint32_t blend_unscaled = src_channel * src_a + dst_channel * dst_a;
  assert(blend_unscaled < (1ULL << 32) / scale);
  return (blend_unscaled * scale) >> 24;
}