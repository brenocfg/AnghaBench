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
typedef  int /*<<< orphan*/  DTable_max_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int FSEv07_MAX_SYMBOL_VALUE ; 
 size_t FSEv07_buildDTable (int /*<<< orphan*/ ,short*,unsigned int,unsigned int) ; 
 size_t FSEv07_decompress_usingDTable (void*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ FSEv07_isError (size_t const) ; 
 size_t FSEv07_readNCount (short*,unsigned int*,unsigned int*,int /*<<< orphan*/  const* const,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t FSEv07_decompress(void* dst, size_t maxDstSize, const void* cSrc, size_t cSrcSize)
{
    const BYTE* const istart = (const BYTE*)cSrc;
    const BYTE* ip = istart;
    short counting[FSEv07_MAX_SYMBOL_VALUE+1];
    DTable_max_t dt;   /* Static analyzer seems unable to understand this table will be properly initialized later */
    unsigned tableLog;
    unsigned maxSymbolValue = FSEv07_MAX_SYMBOL_VALUE;

    if (cSrcSize<2) return ERROR(srcSize_wrong);   /* too small input size */

    /* normal FSE decoding mode */
    {   size_t const NCountLength = FSEv07_readNCount (counting, &maxSymbolValue, &tableLog, istart, cSrcSize);
        if (FSEv07_isError(NCountLength)) return NCountLength;
        if (NCountLength >= cSrcSize) return ERROR(srcSize_wrong);   /* too small input size */
        ip += NCountLength;
        cSrcSize -= NCountLength;
    }

    { size_t const errorCode = FSEv07_buildDTable (dt, counting, maxSymbolValue, tableLog);
      if (FSEv07_isError(errorCode)) return errorCode; }

    return FSEv07_decompress_usingDTable (dst, maxDstSize, ip, cSrcSize, dt);   /* always return, even if it is an error code */
}