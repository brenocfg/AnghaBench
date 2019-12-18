#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U64 ;
typedef  unsigned int U32 ;
struct TYPE_7__ {size_t const* samplesSizes; unsigned int nbSamples; unsigned int nbTrainSamples; unsigned int nbTestSamples; size_t suffixSize; unsigned int* suffix; unsigned int* dmerAt; size_t* offsets; unsigned int* freqs; unsigned int d; int /*<<< orphan*/ * samples; } ;
typedef  TYPE_1__ COVER_ctx_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int COVER_MAX_SAMPLES_SIZE ; 
 int /*<<< orphan*/  COVER_cmp ; 
 int /*<<< orphan*/  COVER_cmp8 ; 
 int /*<<< orphan*/  COVER_ctx_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  COVER_group ; 
 int /*<<< orphan*/  COVER_groupBy (unsigned int*,unsigned int,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COVER_strict_cmp ; 
 int /*<<< orphan*/  COVER_strict_cmp8 ; 
 size_t const COVER_sum (size_t const*,unsigned int const) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t const MAX (unsigned int,int) ; 
 TYPE_1__* g_ctx ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memory_allocation ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mergesort (unsigned int*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsort (unsigned int*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t COVER_ctx_init(COVER_ctx_t *ctx, const void *samplesBuffer,
                          const size_t *samplesSizes, unsigned nbSamples,
                          unsigned d, double splitPoint) {
  const BYTE *const samples = (const BYTE *)samplesBuffer;
  const size_t totalSamplesSize = COVER_sum(samplesSizes, nbSamples);
  /* Split samples into testing and training sets */
  const unsigned nbTrainSamples = splitPoint < 1.0 ? (unsigned)((double)nbSamples * splitPoint) : nbSamples;
  const unsigned nbTestSamples = splitPoint < 1.0 ? nbSamples - nbTrainSamples : nbSamples;
  const size_t trainingSamplesSize = splitPoint < 1.0 ? COVER_sum(samplesSizes, nbTrainSamples) : totalSamplesSize;
  const size_t testSamplesSize = splitPoint < 1.0 ? COVER_sum(samplesSizes + nbTrainSamples, nbTestSamples) : totalSamplesSize;
  /* Checks */
  if (totalSamplesSize < MAX(d, sizeof(U64)) ||
      totalSamplesSize >= (size_t)COVER_MAX_SAMPLES_SIZE) {
    DISPLAYLEVEL(1, "Total samples size is too large (%u MB), maximum size is %u MB\n",
                 (unsigned)(totalSamplesSize>>20), (COVER_MAX_SAMPLES_SIZE >> 20));
    return ERROR(srcSize_wrong);
  }
  /* Check if there are at least 5 training samples */
  if (nbTrainSamples < 5) {
    DISPLAYLEVEL(1, "Total number of training samples is %u and is invalid.", nbTrainSamples);
    return ERROR(srcSize_wrong);
  }
  /* Check if there's testing sample */
  if (nbTestSamples < 1) {
    DISPLAYLEVEL(1, "Total number of testing samples is %u and is invalid.", nbTestSamples);
    return ERROR(srcSize_wrong);
  }
  /* Zero the context */
  memset(ctx, 0, sizeof(*ctx));
  DISPLAYLEVEL(2, "Training on %u samples of total size %u\n", nbTrainSamples,
               (unsigned)trainingSamplesSize);
  DISPLAYLEVEL(2, "Testing on %u samples of total size %u\n", nbTestSamples,
               (unsigned)testSamplesSize);
  ctx->samples = samples;
  ctx->samplesSizes = samplesSizes;
  ctx->nbSamples = nbSamples;
  ctx->nbTrainSamples = nbTrainSamples;
  ctx->nbTestSamples = nbTestSamples;
  /* Partial suffix array */
  ctx->suffixSize = trainingSamplesSize - MAX(d, sizeof(U64)) + 1;
  ctx->suffix = (U32 *)malloc(ctx->suffixSize * sizeof(U32));
  /* Maps index to the dmerID */
  ctx->dmerAt = (U32 *)malloc(ctx->suffixSize * sizeof(U32));
  /* The offsets of each file */
  ctx->offsets = (size_t *)malloc((nbSamples + 1) * sizeof(size_t));
  if (!ctx->suffix || !ctx->dmerAt || !ctx->offsets) {
    DISPLAYLEVEL(1, "Failed to allocate scratch buffers\n");
    COVER_ctx_destroy(ctx);
    return ERROR(memory_allocation);
  }
  ctx->freqs = NULL;
  ctx->d = d;

  /* Fill offsets from the samplesSizes */
  {
    U32 i;
    ctx->offsets[0] = 0;
    for (i = 1; i <= nbSamples; ++i) {
      ctx->offsets[i] = ctx->offsets[i - 1] + samplesSizes[i - 1];
    }
  }
  DISPLAYLEVEL(2, "Constructing partial suffix array\n");
  {
    /* suffix is a partial suffix array.
     * It only sorts suffixes by their first parameters.d bytes.
     * The sort is stable, so each dmer group is sorted by position in input.
     */
    U32 i;
    for (i = 0; i < ctx->suffixSize; ++i) {
      ctx->suffix[i] = i;
    }
    /* qsort doesn't take an opaque pointer, so pass as a global.
     * On OpenBSD qsort() is not guaranteed to be stable, their mergesort() is.
     */
    g_ctx = ctx;
#if defined(__OpenBSD__)
    mergesort(ctx->suffix, ctx->suffixSize, sizeof(U32),
          (ctx->d <= 8 ? &COVER_strict_cmp8 : &COVER_strict_cmp));
#else
    qsort(ctx->suffix, ctx->suffixSize, sizeof(U32),
          (ctx->d <= 8 ? &COVER_strict_cmp8 : &COVER_strict_cmp));
#endif
  }
  DISPLAYLEVEL(2, "Computing frequencies\n");
  /* For each dmer group (group of positions with the same first d bytes):
   * 1. For each position we set dmerAt[position] = dmerID.  The dmerID is
   *    (groupBeginPtr - suffix).  This allows us to go from position to
   *    dmerID so we can look up values in freq.
   * 2. We calculate how many samples the dmer occurs in and save it in
   *    freqs[dmerId].
   */
  COVER_groupBy(ctx->suffix, ctx->suffixSize, sizeof(U32), ctx,
                (ctx->d <= 8 ? &COVER_cmp8 : &COVER_cmp), &COVER_group);
  ctx->freqs = ctx->suffix;
  ctx->suffix = NULL;
  return 0;
}