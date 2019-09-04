#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U64 ;
typedef  unsigned int U32 ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_6__ {size_t const* samplesSizes; unsigned int nbSamples; unsigned int nbTrainSamples; unsigned int nbTestSamples; size_t nbDmers; unsigned int d; size_t* offsets; unsigned int* freqs; int /*<<< orphan*/ * segmentFreqs; int /*<<< orphan*/ * samples; } ;
typedef  TYPE_1__ FASTCOVER_ctx_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int FASTCOVER_MAX_SAMPLES_SIZE ; 
 int /*<<< orphan*/  FASTCOVER_computeFrequency (unsigned int*,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  FASTCOVER_ctx_destroy (TYPE_1__*) ; 
 size_t const FASTCOVER_sum (size_t const*,unsigned int const) ; 
 size_t const MAX (unsigned int,int) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int FASTCOVER_ctx_init(FASTCOVER_ctx_t *ctx, const void *samplesBuffer,
                          const size_t *samplesSizes, unsigned nbSamples,
                          unsigned d, double splitPoint, unsigned f) {
  const BYTE *const samples = (const BYTE *)samplesBuffer;
  const size_t totalSamplesSize = FASTCOVER_sum(samplesSizes, nbSamples);
  /* Split samples into testing and training sets */
  const unsigned nbTrainSamples = splitPoint < 1.0 ? (unsigned)((double)nbSamples * splitPoint) : nbSamples;
  const unsigned nbTestSamples = splitPoint < 1.0 ? nbSamples - nbTrainSamples : nbSamples;
  const size_t trainingSamplesSize = splitPoint < 1.0 ? FASTCOVER_sum(samplesSizes, nbTrainSamples) : totalSamplesSize;
  const size_t testSamplesSize = splitPoint < 1.0 ? FASTCOVER_sum(samplesSizes + nbTrainSamples, nbTestSamples) : totalSamplesSize;
  /* Checks */
  if (totalSamplesSize < MAX(d, sizeof(U64)) ||
      totalSamplesSize >= (size_t)FASTCOVER_MAX_SAMPLES_SIZE) {
    DISPLAYLEVEL(1, "Total samples size is too large (%u MB), maximum size is %u MB\n",
                 (U32)(totalSamplesSize >> 20), (FASTCOVER_MAX_SAMPLES_SIZE >> 20));
    return 0;
  }
  /* Check if there are at least 5 training samples */
  if (nbTrainSamples < 5) {
    DISPLAYLEVEL(1, "Total number of training samples is %u and is invalid.", nbTrainSamples);
    return 0;
  }
  /* Check if there's testing sample */
  if (nbTestSamples < 1) {
    DISPLAYLEVEL(1, "Total number of testing samples is %u and is invalid.", nbTestSamples);
    return 0;
  }
  /* Zero the context */
  memset(ctx, 0, sizeof(*ctx));
  DISPLAYLEVEL(2, "Training on %u samples of total size %u\n", nbTrainSamples,
               (U32)trainingSamplesSize);
  DISPLAYLEVEL(2, "Testing on %u samples of total size %u\n", nbTestSamples,
               (U32)testSamplesSize);

  ctx->samples = samples;
  ctx->samplesSizes = samplesSizes;
  ctx->nbSamples = nbSamples;
  ctx->nbTrainSamples = nbTrainSamples;
  ctx->nbTestSamples = nbTestSamples;
  ctx->nbDmers = trainingSamplesSize - d + 1;
  ctx->d = d;

  /* The offsets of each file */
  ctx->offsets = (size_t *)malloc((nbSamples + 1) * sizeof(size_t));
  if (!ctx->offsets) {
    DISPLAYLEVEL(1, "Failed to allocate scratch buffers\n");
    FASTCOVER_ctx_destroy(ctx);
    return 0;
  }

  /* Fill offsets from the samplesSizes */
  {
    U32 i;
    ctx->offsets[0] = 0;
    for (i = 1; i <= nbSamples; ++i) {
      ctx->offsets[i] = ctx->offsets[i - 1] + samplesSizes[i - 1];
    }
  }

  /* Initialize frequency array of size 2^f */
  ctx->freqs = (U32 *)calloc((1 << f), sizeof(U32));
  ctx->segmentFreqs = (U16 *)calloc((1 << f), sizeof(U16));
  DISPLAYLEVEL(2, "Computing frequencies\n");
  FASTCOVER_computeFrequency(ctx->freqs, f, ctx);

  return 1;
}