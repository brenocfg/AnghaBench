#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZDICT_cover_params_t ;
typedef  int U64 ;
struct TYPE_15__ {size_t dictBufferCapacity; int /*<<< orphan*/  best; int /*<<< orphan*/  parameters; TYPE_5__* ctx; } ;
typedef  TYPE_2__ U32 ;
typedef  TYPE_2__ U16 ;
struct TYPE_14__ {int finalize; } ;
struct TYPE_16__ {int f; int nbTrainSamples; int /*<<< orphan*/  offsets; int /*<<< orphan*/  nbSamples; int /*<<< orphan*/  samplesSizes; int /*<<< orphan*/  samples; TYPE_1__ accelParams; int /*<<< orphan*/  freqs; } ;
typedef  TYPE_2__ FASTCOVER_tryParameters_data_t ;
typedef  TYPE_5__ FASTCOVER_ctx_t ;
typedef  int /*<<< orphan*/  COVER_dictSelection_t ;
typedef  TYPE_2__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  COVER_best_finish (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COVER_dictSelectionError (size_t) ; 
 int /*<<< orphan*/  COVER_dictSelectionFree (int /*<<< orphan*/ ) ; 
 scalar_t__ COVER_dictSelectionIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COVER_selectDict (TYPE_2__* const,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t FASTCOVER_buildDictionary (TYPE_5__ const* const,TYPE_2__*,TYPE_2__* const,size_t,int /*<<< orphan*/  const,TYPE_2__*) ; 
 int /*<<< orphan*/  GENERIC ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__* const) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

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
  COVER_dictSelection_t selection = COVER_dictSelectionError(ERROR(GENERIC));
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
    selection = COVER_selectDict(dict + tail, dictBufferCapacity - tail,
         ctx->samples, ctx->samplesSizes, nbFinalizeSamples, ctx->nbTrainSamples, ctx->nbSamples, parameters, ctx->offsets,
         totalCompressedSize);

    if (COVER_dictSelectionIsError(selection)) {
      DISPLAYLEVEL(1, "Failed to select dictionary\n");
      goto _cleanup;
    }
  }
_cleanup:
  free(dict);
  COVER_best_finish(data->best, parameters, selection);
  free(data);
  free(segmentFreqs);
  COVER_dictSelectionFree(selection);
  free(freqs);
}