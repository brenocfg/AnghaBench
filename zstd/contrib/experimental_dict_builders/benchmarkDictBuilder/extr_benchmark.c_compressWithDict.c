#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nbSamples; size_t* samplesSizes; scalar_t__ srcBuffer; } ;
typedef  TYPE_1__ sampleInfo ;
struct TYPE_6__ {scalar_t__ dictSize; int /*<<< orphan*/  dictBuffer; } ;
typedef  TYPE_2__ dictInfo ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,size_t) ; 
 size_t MAX (size_t,size_t) ; 
 size_t ZSTD_compressBound (size_t) ; 
 size_t ZSTD_compressCCtx (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const* const,size_t,int) ; 
 size_t ZSTD_compress_usingCDict (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const* const,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createCDict (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 void* malloc (int) ; 

double compressWithDict(sampleInfo *srcInfo, dictInfo* dInfo, int compressionLevel, int displayLevel) {
  /* Local variables */
  size_t totalCompressedSize = 0;
  size_t totalOriginalSize = 0;
  const unsigned hasDict = dInfo->dictSize > 0 ? 1 : 0;
  double cRatio;
  size_t dstCapacity;
  int i;

  /* Pointers */
  ZSTD_CDict *cdict = NULL;
  ZSTD_CCtx* cctx = NULL;
  size_t *offsets = NULL;
  void* dst = NULL;

  /* Allocate dst with enough space to compress the maximum sized sample */
  {
    size_t maxSampleSize = 0;
    for (i = 0; i < srcInfo->nbSamples; i++) {
      maxSampleSize = MAX(srcInfo->samplesSizes[i], maxSampleSize);
    }
    dstCapacity = ZSTD_compressBound(maxSampleSize);
    dst = malloc(dstCapacity);
  }

  /* Calculate offset for each sample */
  offsets = (size_t *)malloc((srcInfo->nbSamples + 1) * sizeof(size_t));
  offsets[0] = 0;
  for (i = 1; i <= srcInfo->nbSamples; i++) {
    offsets[i] = offsets[i - 1] + srcInfo->samplesSizes[i - 1];
  }

  /* Create the cctx */
  cctx = ZSTD_createCCtx();
  if(!cctx || !dst) {
    cRatio = -1;
    goto _cleanup;
  }

  /* Create CDict if there's a dictionary stored on buffer */
  if (hasDict) {
    cdict = ZSTD_createCDict(dInfo->dictBuffer, dInfo->dictSize, compressionLevel);
    if(!cdict) {
      cRatio = -1;
      goto _cleanup;
    }
  }

  /* Compress each sample and sum their sizes*/
  const BYTE *const samples = (const BYTE *)srcInfo->srcBuffer;
  for (i = 0; i < srcInfo->nbSamples; i++) {
    size_t compressedSize;
    if(hasDict) {
      compressedSize = ZSTD_compress_usingCDict(cctx, dst, dstCapacity, samples + offsets[i], srcInfo->samplesSizes[i], cdict);
    } else {
      compressedSize = ZSTD_compressCCtx(cctx, dst, dstCapacity,samples + offsets[i], srcInfo->samplesSizes[i], compressionLevel);
    }
    if (ZSTD_isError(compressedSize)) {
      cRatio = -1;
      goto _cleanup;
    }
    totalCompressedSize += compressedSize;
  }

  /* Sum original sizes */
  for (i = 0; i<srcInfo->nbSamples; i++) {
    totalOriginalSize += srcInfo->samplesSizes[i];
  }

  /* Calculate compression ratio */
  DISPLAYLEVEL(2, "original size is %lu\n", totalOriginalSize);
  DISPLAYLEVEL(2, "compressed size is %lu\n", totalCompressedSize);
  cRatio = (double)totalOriginalSize/(double)totalCompressedSize;

_cleanup:
  free(dst);
  free(offsets);
  ZSTD_freeCCtx(cctx);
  ZSTD_freeCDict(cdict);
  return cRatio;
}