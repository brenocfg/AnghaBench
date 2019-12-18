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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  VP8Matrix ;

/* Variables and functions */
 int VP8EncQuantizeBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 

__attribute__((used)) static int Quantize2Blocks_C(int16_t in[32], int16_t out[32],
                             const VP8Matrix* const mtx) {
  int nz;
  nz  = VP8EncQuantizeBlock(in + 0 * 16, out + 0 * 16, mtx) << 0;
  nz |= VP8EncQuantizeBlock(in + 1 * 16, out + 1 * 16, mtx) << 1;
  return nz;
}