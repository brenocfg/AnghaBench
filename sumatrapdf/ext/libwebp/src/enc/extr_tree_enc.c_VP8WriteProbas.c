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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__**** coeffs_; scalar_t__ const skip_proba_; int /*<<< orphan*/  use_skip_proba_; } ;
typedef  TYPE_1__ VP8EncProba ;
typedef  int /*<<< orphan*/  VP8BitWriter ;

/* Variables and functions */
 int NUM_BANDS ; 
 int NUM_CTX ; 
 int NUM_PROBAS ; 
 int NUM_TYPES ; 
 scalar_t__ const**** VP8CoeffsProba0 ; 
 int /*<<< orphan*/ **** VP8CoeffsUpdateProba ; 
 scalar_t__ VP8PutBit (int /*<<< orphan*/ * const,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ VP8PutBitUniform (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8PutBits (int /*<<< orphan*/ * const,scalar_t__ const,int) ; 

void VP8WriteProbas(VP8BitWriter* const bw, const VP8EncProba* const probas) {
  int t, b, c, p;
  for (t = 0; t < NUM_TYPES; ++t) {
    for (b = 0; b < NUM_BANDS; ++b) {
      for (c = 0; c < NUM_CTX; ++c) {
        for (p = 0; p < NUM_PROBAS; ++p) {
          const uint8_t p0 = probas->coeffs_[t][b][c][p];
          const int update = (p0 != VP8CoeffsProba0[t][b][c][p]);
          if (VP8PutBit(bw, update, VP8CoeffsUpdateProba[t][b][c][p])) {
            VP8PutBits(bw, p0, 8);
          }
        }
      }
    }
  }
  if (VP8PutBitUniform(bw, probas->use_skip_proba_)) {
    VP8PutBits(bw, probas->skip_proba_, 8);
  }
}