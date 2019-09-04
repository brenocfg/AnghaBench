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
typedef  scalar_t__ ptr ;
typedef  scalar_t__ cSrc ;
typedef  int U32 ;
typedef  int U16 ;
struct TYPE_6__ {char* start; int /*<<< orphan*/  bitContainer; int /*<<< orphan*/  bitsConsumed; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  HUF_DElt ;
typedef  TYPE_1__ FSE_DStream_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FSE_32bits () ; 
 int FSE_DStream_completed ; 
 int /*<<< orphan*/  FSE_ERROR_corruptionDetected ; 
 int /*<<< orphan*/  FSE_ERROR_dstSize_tooSmall ; 
 int /*<<< orphan*/  FSE_ERROR_srcSize_wrong ; 
 scalar_t__ FSE_endOfDStream (TYPE_1__*) ; 
 size_t FSE_initDStream (TYPE_1__*,char const* const,size_t const) ; 
 scalar_t__ FSE_isError (size_t) ; 
 size_t FSE_readLE16 (int const*) ; 
 int FSE_reloadDStream (TYPE_1__*) ; 
 int HUF_MAX_TABLELOG ; 
 int /*<<< orphan*/  HUF_decodeSymbol (TYPE_1__*,int /*<<< orphan*/  const* const,int const) ; 

__attribute__((used)) static size_t HUF_decompress_usingDTable(   /* -3% slower when non static */
          void* dst, size_t maxDstSize,
    const void* cSrc, size_t cSrcSize,
    const U16* DTable)
{
    if (cSrcSize < 6) return (size_t)-FSE_ERROR_srcSize_wrong;
    {
        BYTE* const ostart = (BYTE*) dst;
        BYTE* op = ostart;
        BYTE* const omax = op + maxDstSize;
        BYTE* const olimit = omax-15;

        const void* ptr = DTable;
        const HUF_DElt* const dt = (const HUF_DElt*)(ptr)+1;
        const U32 dtLog = DTable[0];
        size_t errorCode;
        U32 reloadStatus;

        /* Init */

        const U16* jumpTable = (const U16*)cSrc;
        const size_t length1 = FSE_readLE16(jumpTable);
        const size_t length2 = FSE_readLE16(jumpTable+1);
        const size_t length3 = FSE_readLE16(jumpTable+2);
        const size_t length4 = cSrcSize - 6 - length1 - length2 - length3;   // check coherency !!
        const char* const start1 = (const char*)(cSrc) + 6;
        const char* const start2 = start1 + length1;
        const char* const start3 = start2 + length2;
        const char* const start4 = start3 + length3;
        FSE_DStream_t bitD1, bitD2, bitD3, bitD4;

        if (length1+length2+length3+6 >= cSrcSize) return (size_t)-FSE_ERROR_srcSize_wrong;

        errorCode = FSE_initDStream(&bitD1, start1, length1);
        if (FSE_isError(errorCode)) return errorCode;
        errorCode = FSE_initDStream(&bitD2, start2, length2);
        if (FSE_isError(errorCode)) return errorCode;
        errorCode = FSE_initDStream(&bitD3, start3, length3);
        if (FSE_isError(errorCode)) return errorCode;
        errorCode = FSE_initDStream(&bitD4, start4, length4);
        if (FSE_isError(errorCode)) return errorCode;

        reloadStatus=FSE_reloadDStream(&bitD2);

        /* 16 symbols per loop */
        for ( ; (reloadStatus<FSE_DStream_completed) && (op<olimit);  /* D2-3-4 are supposed to be synchronized and finish together */
            op+=16, reloadStatus = FSE_reloadDStream(&bitD2) | FSE_reloadDStream(&bitD3) | FSE_reloadDStream(&bitD4), FSE_reloadDStream(&bitD1))
        {
    #define HUF_DECODE_SYMBOL_0(n, Dstream) \
            op[n] = HUF_decodeSymbol(&Dstream, dt, dtLog);

    #define HUF_DECODE_SYMBOL_1(n, Dstream) \
            op[n] = HUF_decodeSymbol(&Dstream, dt, dtLog); \
            if (FSE_32bits() && (HUF_MAX_TABLELOG>12)) FSE_reloadDStream(&Dstream)

    #define HUF_DECODE_SYMBOL_2(n, Dstream) \
            op[n] = HUF_decodeSymbol(&Dstream, dt, dtLog); \
            if (FSE_32bits()) FSE_reloadDStream(&Dstream)

            HUF_DECODE_SYMBOL_1( 0, bitD1);
            HUF_DECODE_SYMBOL_1( 1, bitD2);
            HUF_DECODE_SYMBOL_1( 2, bitD3);
            HUF_DECODE_SYMBOL_1( 3, bitD4);
            HUF_DECODE_SYMBOL_2( 4, bitD1);
            HUF_DECODE_SYMBOL_2( 5, bitD2);
            HUF_DECODE_SYMBOL_2( 6, bitD3);
            HUF_DECODE_SYMBOL_2( 7, bitD4);
            HUF_DECODE_SYMBOL_1( 8, bitD1);
            HUF_DECODE_SYMBOL_1( 9, bitD2);
            HUF_DECODE_SYMBOL_1(10, bitD3);
            HUF_DECODE_SYMBOL_1(11, bitD4);
            HUF_DECODE_SYMBOL_0(12, bitD1);
            HUF_DECODE_SYMBOL_0(13, bitD2);
            HUF_DECODE_SYMBOL_0(14, bitD3);
            HUF_DECODE_SYMBOL_0(15, bitD4);
        }

        if (reloadStatus!=FSE_DStream_completed)   /* not complete : some bitStream might be FSE_DStream_unfinished */
            return (size_t)-FSE_ERROR_corruptionDetected;

        /* tail */
        {
            // bitTail = bitD1;   // *much* slower : -20% !??!
            FSE_DStream_t bitTail;
            bitTail.ptr = bitD1.ptr;
            bitTail.bitsConsumed = bitD1.bitsConsumed;
            bitTail.bitContainer = bitD1.bitContainer;   // required in case of FSE_DStream_endOfBuffer
            bitTail.start = start1;
            for ( ; (FSE_reloadDStream(&bitTail) < FSE_DStream_completed) && (op<omax) ; op++)
            {
                HUF_DECODE_SYMBOL_0(0, bitTail);
            }

            if (FSE_endOfDStream(&bitTail))
                return op-ostart;
        }

        if (op==omax) return (size_t)-FSE_ERROR_dstSize_tooSmall;   /* dst buffer is full, but cSrc unfinished */

        return (size_t)-FSE_ERROR_corruptionDetected;
    }
}