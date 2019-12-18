#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_CDict ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
struct TYPE_4__ {int /*<<< orphan*/  compressionLevel; } ;
struct TYPE_5__ {double splitPoint; TYPE_1__ zParams; } ;
typedef  TYPE_2__ ZDICT_cover_params_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t MAX (size_t const,size_t) ; 
 size_t ZSTD_compressBound (size_t) ; 
 size_t ZSTD_compress_usingCDict (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const*,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createCDict (int /*<<< orphan*/ * const,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 

size_t COVER_checkTotalCompressedSize(const ZDICT_cover_params_t parameters,
                                    const size_t *samplesSizes, const BYTE *samples,
                                    size_t *offsets,
                                    size_t nbTrainSamples, size_t nbSamples,
                                    BYTE *const dict, size_t dictBufferCapacity) {
  size_t totalCompressedSize = ERROR(GENERIC);
  /* Pointers */
  ZSTD_CCtx *cctx;
  ZSTD_CDict *cdict;
  void *dst;
  /* Local variables */
  size_t dstCapacity;
  size_t i;
  /* Allocate dst with enough space to compress the maximum sized sample */
  {
    size_t maxSampleSize = 0;
    i = parameters.splitPoint < 1.0 ? nbTrainSamples : 0;
    for (; i < nbSamples; ++i) {
      maxSampleSize = MAX(samplesSizes[i], maxSampleSize);
    }
    dstCapacity = ZSTD_compressBound(maxSampleSize);
    dst = malloc(dstCapacity);
  }
  /* Create the cctx and cdict */
  cctx = ZSTD_createCCtx();
  cdict = ZSTD_createCDict(dict, dictBufferCapacity,
                           parameters.zParams.compressionLevel);
  if (!dst || !cctx || !cdict) {
    goto _compressCleanup;
  }
  /* Compress each sample and sum their sizes (or error) */
  totalCompressedSize = dictBufferCapacity;
  i = parameters.splitPoint < 1.0 ? nbTrainSamples : 0;
  for (; i < nbSamples; ++i) {
    const size_t size = ZSTD_compress_usingCDict(
        cctx, dst, dstCapacity, samples + offsets[i],
        samplesSizes[i], cdict);
    if (ZSTD_isError(size)) {
      totalCompressedSize = size;
      goto _compressCleanup;
    }
    totalCompressedSize += size;
  }
_compressCleanup:
  ZSTD_freeCCtx(cctx);
  ZSTD_freeCDict(cdict);
  if (dst) {
    free(dst);
  }
  return totalCompressedSize;
}