#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  zParams; scalar_t__ d; scalar_t__ k; } ;
typedef  TYPE_1__ ZDICT_cover_params_t ;
struct TYPE_19__ {size_t dictBufferCapacity; int /*<<< orphan*/  best; TYPE_1__ parameters; TYPE_4__* ctx; } ;
typedef  TYPE_2__ U32 ;
struct TYPE_20__ {int suffixSize; int /*<<< orphan*/  nbSamples; scalar_t__ nbTrainSamples; int /*<<< orphan*/  offsets; int /*<<< orphan*/  samples; int /*<<< orphan*/  samplesSizes; int /*<<< orphan*/  freqs; } ;
typedef  TYPE_2__ COVER_tryParameters_data_t ;
typedef  int /*<<< orphan*/  COVER_map_t ;
typedef  TYPE_4__ COVER_ctx_t ;
typedef  TYPE_2__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  COVER_best_finish (int /*<<< orphan*/ ,size_t,TYPE_1__ const,TYPE_2__* const,size_t) ; 
 size_t COVER_buildDictionary (TYPE_4__ const* const,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__* const,size_t,TYPE_1__ const) ; 
 size_t COVER_checkTotalCompressedSize (TYPE_1__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__* const,size_t) ; 
 int /*<<< orphan*/  COVER_map_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COVER_map_init (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t ZDICT_finalizeDictionary (TYPE_2__* const,size_t,TYPE_2__* const,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ZDICT_isError (size_t) ; 
 int /*<<< orphan*/  free (TYPE_2__* const) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void COVER_tryParameters(void *opaque) {
  /* Save parameters as local variables */
  COVER_tryParameters_data_t *const data = (COVER_tryParameters_data_t *)opaque;
  const COVER_ctx_t *const ctx = data->ctx;
  const ZDICT_cover_params_t parameters = data->parameters;
  size_t dictBufferCapacity = data->dictBufferCapacity;
  size_t totalCompressedSize = ERROR(GENERIC);
  /* Allocate space for hash table, dict, and freqs */
  COVER_map_t activeDmers;
  BYTE *const dict = (BYTE * const)malloc(dictBufferCapacity);
  U32 *freqs = (U32 *)malloc(ctx->suffixSize * sizeof(U32));
  if (!COVER_map_init(&activeDmers, parameters.k - parameters.d + 1)) {
    DISPLAYLEVEL(1, "Failed to allocate dmer map: out of memory\n");
    goto _cleanup;
  }
  if (!dict || !freqs) {
    DISPLAYLEVEL(1, "Failed to allocate buffers: out of memory\n");
    goto _cleanup;
  }
  /* Copy the frequencies because we need to modify them */
  memcpy(freqs, ctx->freqs, ctx->suffixSize * sizeof(U32));
  /* Build the dictionary */
  {
    const size_t tail = COVER_buildDictionary(ctx, freqs, &activeDmers, dict,
                                              dictBufferCapacity, parameters);
    dictBufferCapacity = ZDICT_finalizeDictionary(
        dict, dictBufferCapacity, dict + tail, dictBufferCapacity - tail,
        ctx->samples, ctx->samplesSizes, (unsigned)ctx->nbTrainSamples,
        parameters.zParams);
    if (ZDICT_isError(dictBufferCapacity)) {
      DISPLAYLEVEL(1, "Failed to finalize dictionary\n");
      goto _cleanup;
    }
  }
  /* Check total compressed size */
  totalCompressedSize = COVER_checkTotalCompressedSize(parameters, ctx->samplesSizes,
                                                       ctx->samples, ctx->offsets,
                                                       ctx->nbTrainSamples, ctx->nbSamples,
                                                       dict, dictBufferCapacity);

_cleanup:
  COVER_best_finish(data->best, totalCompressedSize, parameters, dict,
                    dictBufferCapacity);
  free(data);
  COVER_map_destroy(&activeDmers);
  if (dict) {
    free(dict);
  }
  if (freqs) {
    free(freqs);
  }
}