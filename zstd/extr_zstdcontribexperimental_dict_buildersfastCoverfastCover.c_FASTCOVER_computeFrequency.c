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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {unsigned int nbTrainSamples; size_t* offsets; size_t d; scalar_t__ samples; } ;
typedef  TYPE_1__ FASTCOVER_ctx_t ;

/* Variables and functions */
 size_t FASTCOVER_hashPtrToIndex (scalar_t__,unsigned int,size_t) ; 

__attribute__((used)) static void FASTCOVER_computeFrequency(U32 *freqs, unsigned f, FASTCOVER_ctx_t *ctx){
  size_t start; /* start of current dmer */
  for (unsigned i = 0; i < ctx->nbTrainSamples; i++) {
    size_t currSampleStart = ctx->offsets[i];
    size_t currSampleEnd = ctx->offsets[i+1];
    start = currSampleStart;
    while (start + ctx->d <= currSampleEnd) {
      const size_t dmerIndex = FASTCOVER_hashPtrToIndex(ctx->samples + start, f, ctx->d);
      freqs[dmerIndex]++;
      start++;
    }
  }
}