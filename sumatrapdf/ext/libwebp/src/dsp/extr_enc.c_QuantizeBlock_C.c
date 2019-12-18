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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_3__ {scalar_t__* sharpen_; scalar_t__ const* zthresh_; scalar_t__* q_; scalar_t__* iq_; scalar_t__* bias_; } ;
typedef  TYPE_1__ VP8Matrix ;

/* Variables and functions */
 int MAX_LEVEL ; 
 int QUANTDIV (scalar_t__ const,scalar_t__ const,scalar_t__ const) ; 
 int* kZigzag ; 

__attribute__((used)) static int QuantizeBlock_C(int16_t in[16], int16_t out[16],
                           const VP8Matrix* const mtx) {
  int last = -1;
  int n;
  for (n = 0; n < 16; ++n) {
    const int j = kZigzag[n];
    const int sign = (in[j] < 0);
    const uint32_t coeff = (sign ? -in[j] : in[j]) + mtx->sharpen_[j];
    if (coeff > mtx->zthresh_[j]) {
      const uint32_t Q = mtx->q_[j];
      const uint32_t iQ = mtx->iq_[j];
      const uint32_t B = mtx->bias_[j];
      int level = QUANTDIV(coeff, iQ, B);
      if (level > MAX_LEVEL) level = MAX_LEVEL;
      if (sign) level = -level;
      in[j] = level * (int)Q;
      out[n] = level;
      if (level) last = n;
    } else {
      out[n] = 0;
      in[j] = 0;
    }
  }
  return (last >= 0);
}