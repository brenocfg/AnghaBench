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
typedef  int /*<<< orphan*/  VP8Random ;

/* Variables and functions */
 int /*<<< orphan*/  VP8DitherCombine8x8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8RandomBits2 (int /*<<< orphan*/ * const,scalar_t__,int) ; 
 scalar_t__ VP8_DITHER_AMP_BITS ; 

__attribute__((used)) static void Dither8x8(VP8Random* const rg, uint8_t* dst, int bps, int amp) {
  uint8_t dither[64];
  int i;
  for (i = 0; i < 8 * 8; ++i) {
    dither[i] = VP8RandomBits2(rg, VP8_DITHER_AMP_BITS + 1, amp);
  }
  VP8DitherCombine8x8(dither, dst, bps);
}