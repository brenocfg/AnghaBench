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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int* quant_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/ * VP8ProbaArray ;
typedef  int /*<<< orphan*/  VP8BitReader ;
struct TYPE_3__ {int /*<<< orphan*/ ** probas_; } ;
typedef  TYPE_1__ VP8BandProbas ;

/* Variables and functions */
 int GetLargeValue (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VP8GetBitAlt (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,char*) ; 
 int VP8GetSigned (int /*<<< orphan*/ * const,int,char*) ; 
 size_t* kZigzag ; 

__attribute__((used)) static int GetCoeffsAlt(VP8BitReader* const br,
                        const VP8BandProbas* const prob[],
                        int ctx, const quant_t dq, int n, int16_t* out) {
  const uint8_t* p = prob[n]->probas_[ctx];
  for (; n < 16; ++n) {
    if (!VP8GetBitAlt(br, p[0], "coeffs")) {
      return n;  // previous coeff was last non-zero coeff
    }
    while (!VP8GetBitAlt(br, p[1], "coeffs")) {       // sequence of zero coeffs
      p = prob[++n]->probas_[0];
      if (n == 16) return 16;
    }
    {        // non zero coeff
      const VP8ProbaArray* const p_ctx = &prob[n + 1]->probas_[0];
      int v;
      if (!VP8GetBitAlt(br, p[2], "coeffs")) {
        v = 1;
        p = p_ctx[1];
      } else {
        v = GetLargeValue(br, p);
        p = p_ctx[2];
      }
      out[kZigzag[n]] = VP8GetSigned(br, v, "coeffs") * dq[n > 0];
    }
  }
  return 16;
}