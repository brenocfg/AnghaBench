#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  scratchBuffer ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  FSE_CTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_V_F (scalar_t__,int /*<<< orphan*/ ) ; 
 int FSE_CTABLE_SIZE_U32 (int,int) ; 
 int /*<<< orphan*/  FSE_buildCTable_wksp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FSE_compress_usingCTable (int /*<<< orphan*/ *,int,void const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSE_normalizeCount (int /*<<< orphan*/ *,int,int*,size_t,int) ; 
 int FSE_optimalTableLog (int,size_t,int) ; 
 int /*<<< orphan*/  FSE_writeNCount (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 unsigned int HIST_count_simple (int*,int*,void const*,size_t) ; 
 int HUF_TABLELOG_MAX ; 
 int MAX_FSE_TABLELOG_FOR_HUFF_HEADER ; 
 scalar_t__ cSize ; 
 scalar_t__ hSize ; 

__attribute__((used)) static size_t HUF_compressWeights (void* dst, size_t dstSize, const void* weightTable, size_t wtSize)
{
    BYTE* const ostart = (BYTE*) dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + dstSize;

    U32 maxSymbolValue = HUF_TABLELOG_MAX;
    U32 tableLog = MAX_FSE_TABLELOG_FOR_HUFF_HEADER;

    FSE_CTable CTable[FSE_CTABLE_SIZE_U32(MAX_FSE_TABLELOG_FOR_HUFF_HEADER, HUF_TABLELOG_MAX)];
    BYTE scratchBuffer[1<<MAX_FSE_TABLELOG_FOR_HUFF_HEADER];

    U32 count[HUF_TABLELOG_MAX+1];
    S16 norm[HUF_TABLELOG_MAX+1];

    /* init conditions */
    if (wtSize <= 1) return 0;  /* Not compressible */

    /* Scan input and build symbol stats */
    {   unsigned const maxCount = HIST_count_simple(count, &maxSymbolValue, weightTable, wtSize);   /* never fails */
        if (maxCount == wtSize) return 1;   /* only a single symbol in src : rle */
        if (maxCount == 1) return 0;        /* each symbol present maximum once => not compressible */
    }

    tableLog = FSE_optimalTableLog(tableLog, wtSize, maxSymbolValue);
    CHECK_F( FSE_normalizeCount(norm, tableLog, count, wtSize, maxSymbolValue) );

    /* Write table description header */
    {   CHECK_V_F(hSize, FSE_writeNCount(op, oend-op, norm, maxSymbolValue, tableLog) );
        op += hSize;
    }

    /* Compress */
    CHECK_F( FSE_buildCTable_wksp(CTable, norm, maxSymbolValue, tableLog, scratchBuffer, sizeof(scratchBuffer)) );
    {   CHECK_V_F(cSize, FSE_compress_usingCTable(op, oend - op, weightTable, wtSize, CTable) );
        if (cSize == 0) return 0;   /* not enough space for compressed data */
        op += cSize;
    }

    return op-ostart;
}