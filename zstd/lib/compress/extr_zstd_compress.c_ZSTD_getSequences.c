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
typedef  int /*<<< orphan*/  ZSTD_Sequence ;
struct TYPE_6__ {int collectSequences; size_t seqIndex; size_t maxSequences; int /*<<< orphan*/ * seqStart; } ;
struct TYPE_5__ {TYPE_2__ seqCollector; } ;
typedef  TYPE_1__ ZSTD_CCtx ;
typedef  TYPE_2__ SeqCollector ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_ERROR_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_compress2 (TYPE_1__*,void*,size_t const,void const*,size_t) ; 
 size_t ZSTD_compressBound (size_t) ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 
 int /*<<< orphan*/  ZSTD_free (void*,int /*<<< orphan*/ ) ; 
 void* ZSTD_malloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTD_getSequences(ZSTD_CCtx* zc, ZSTD_Sequence* outSeqs,
    size_t outSeqsSize, const void* src, size_t srcSize)
{
    const size_t dstCapacity = ZSTD_compressBound(srcSize);
    void* dst = ZSTD_malloc(dstCapacity, ZSTD_defaultCMem);
    SeqCollector seqCollector;

    RETURN_ERROR_IF(dst == NULL, memory_allocation);

    seqCollector.collectSequences = 1;
    seqCollector.seqStart = outSeqs;
    seqCollector.seqIndex = 0;
    seqCollector.maxSequences = outSeqsSize;
    zc->seqCollector = seqCollector;

    ZSTD_compress2(zc, dst, dstCapacity, src, srcSize);
    ZSTD_free(dst, ZSTD_defaultCMem);
    return zc->seqCollector.seqIndex;
}