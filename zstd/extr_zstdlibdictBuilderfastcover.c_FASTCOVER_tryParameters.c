#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  zParams; } ;
typedef  TYPE_2__ ZDICT_cover_params_t ;
typedef  int U64 ;
struct TYPE_23__ {size_t dictBufferCapacity; int /*<<< orphan*/  best; TYPE_2__ parameters; TYPE_6__* ctx; } ;
typedef  TYPE_3__ U32 ;
typedef  TYPE_3__ U16 ;
struct TYPE_21__ {int finalize; } ;
struct TYPE_24__ {int f; int nbTrainSamples; int /*<<< orphan*/  nbSamples; int /*<<< orphan*/  offsets; int /*<<< orphan*/  samples; int /*<<< orphan*/  samplesSizes; TYPE_1__ accelParams; int /*<<< orphan*/  freqs; } ;
typedef  TYPE_3__ FASTCOVER_tryParameters_data_t ;
typedef  TYPE_6__ FASTCOVER_ctx_t ;
typedef  TYPE_3__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  COVER_best_finish (int /*<<< orphan*/ ,size_t,TYPE_2__ const,TYPE_3__* const,size_t) ; 
 size_t COVER_checkTotalCompressedSize (TYPE_2__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__* const,size_t) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t FASTCOVER_buildDictionary (TYPE_6__ const* const,TYPE_3__*,TYPE_3__* const,size_t,TYPE_2__ const,TYPE_3__*) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t ZDICT_finalizeDictionary (TYPE_3__* const,size_t,TYPE_3__* const,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ) ; 
 scalar_t__ ZDICT_isError (size_t) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__* const) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void FASTCOVER_tryParameters(void *opaque)
{
  /* Save parameters as local variables */
  FASTCOVER_tryParameters_data_t *const data = (FASTCOVER_tryParameters_data_t *)opaque;
  const FASTCOVER_ctx_t *const ctx = data->ctx;
  const ZDICT_cover_params_t parameters = data->parameters;
  size_t dictBufferCapacity = data->dictBufferCapacity;
  size_t totalCompressedSize = ERROR(GENERIC);
  /* Initialize array to keep track of frequency of dmer within activeSegment */
  U16* segmentFreqs = (U16 *)calloc(((U64)1 << ctx->f), sizeof(U16));
  /* Allocate space for hash table, dict, and freqs */
  BYTE *const dict = (BYTE * const)malloc(dictBufferCapacity);
  U32 *freqs = (U32*) malloc(((U64)1 << ctx->f) * sizeof(U32));
  if (!segmentFreqs || !dict || !freqs) {
    DISPLAYLEVEL(1, "Failed to allocate buffers: out of memory\n");
    goto _cleanup;
  }
  /* Copy the frequencies because we need to modify them */
  memcpy(freqs, ctx->freqs, ((U64)1 << ctx->f) * sizeof(U32));
  /* Build the dictionary */
  { const size_t tail = FASTCOVER_buildDictionary(ctx, freqs, dict, dictBufferCapacity,
                                                  parameters, segmentFreqs);
    const unsigned nbFinalizeSamples = (unsigned)(ctx->nbTrainSamples * ctx->accelParams.finalize / 100);
    dictBufferCapacity = ZDICT_finalizeDictionary(
        dict, dictBufferCapacity, dict + tail, dictBufferCapacity - tail,
        ctx->samples, ctx->samplesSizes, nbFinalizeSamples, parameters.zParams);
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
  free(segmentFreqs);
  free(dict);
  free(freqs);
}