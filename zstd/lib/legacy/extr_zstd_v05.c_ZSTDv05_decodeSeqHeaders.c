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
typedef  int U32 ;
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  FSEv05_DTable ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
#define  FSEv05_ENCODING_DYNAMIC 131 
#define  FSEv05_ENCODING_RAW 130 
#define  FSEv05_ENCODING_RLE 129 
#define  FSEv05_ENCODING_STATIC 128 
 int /*<<< orphan*/  FSEv05_buildDTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FSEv05_buildDTable_raw (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  FSEv05_buildDTable_rle (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  FSEv05_isError (size_t) ; 
 size_t FSEv05_readNCount (int /*<<< orphan*/ *,unsigned int*,unsigned int*,int const*,int) ; 
 int /*<<< orphan*/  GENERIC ; 
 unsigned int LLFSEv05Log ; 
 unsigned int LLbits ; 
 size_t MIN_SEQUENCES_SIZE ; 
 unsigned int MLFSEv05Log ; 
 unsigned int MLbits ; 
 unsigned int MaxLL ; 
 unsigned int MaxML ; 
 unsigned int MaxOff ; 
 unsigned int OffFSEv05Log ; 
 unsigned int Offbits ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv05_decodeSeqHeaders(int* nbSeq, const BYTE** dumpsPtr, size_t* dumpsLengthPtr,
                         FSEv05_DTable* DTableLL, FSEv05_DTable* DTableML, FSEv05_DTable* DTableOffb,
                         const void* src, size_t srcSize, U32 flagStaticTable)
{
    const BYTE* const istart = (const BYTE* const)src;
    const BYTE* ip = istart;
    const BYTE* const iend = istart + srcSize;
    U32 LLtype, Offtype, MLtype;
    unsigned LLlog, Offlog, MLlog;
    size_t dumpsLength;

    /* check */
    if (srcSize < MIN_SEQUENCES_SIZE)
        return ERROR(srcSize_wrong);

    /* SeqHead */
    *nbSeq = *ip++;
    if (*nbSeq==0) return 1;
    if (*nbSeq >= 128) {
        if (ip >= iend) return ERROR(srcSize_wrong);
        *nbSeq = ((nbSeq[0]-128)<<8) + *ip++;
    }

    if (ip >= iend) return ERROR(srcSize_wrong);
    LLtype  = *ip >> 6;
    Offtype = (*ip >> 4) & 3;
    MLtype  = (*ip >> 2) & 3;
    if (*ip & 2) {
        if (ip+3 > iend) return ERROR(srcSize_wrong);
        dumpsLength  = ip[2];
        dumpsLength += ip[1] << 8;
        ip += 3;
    } else {
        if (ip+2 > iend) return ERROR(srcSize_wrong);
        dumpsLength  = ip[1];
        dumpsLength += (ip[0] & 1) << 8;
        ip += 2;
    }
    *dumpsPtr = ip;
    ip += dumpsLength;
    *dumpsLengthPtr = dumpsLength;

    /* check */
    if (ip > iend-3) return ERROR(srcSize_wrong); /* min : all 3 are "raw", hence no header, but at least xxLog bits per type */

    /* sequences */
    {
        S16 norm[MaxML+1];    /* assumption : MaxML >= MaxLL >= MaxOff */
        size_t headerSize;

        /* Build DTables */
        switch(LLtype)
        {
        case FSEv05_ENCODING_RLE :
            LLlog = 0;
            FSEv05_buildDTable_rle(DTableLL, *ip++);
            break;
        case FSEv05_ENCODING_RAW :
            LLlog = LLbits;
            FSEv05_buildDTable_raw(DTableLL, LLbits);
            break;
        case FSEv05_ENCODING_STATIC:
            if (!flagStaticTable) return ERROR(corruption_detected);
            break;
        case FSEv05_ENCODING_DYNAMIC :
        default :   /* impossible */
            {   unsigned max = MaxLL;
                headerSize = FSEv05_readNCount(norm, &max, &LLlog, ip, iend-ip);
                if (FSEv05_isError(headerSize)) return ERROR(GENERIC);
                if (LLlog > LLFSEv05Log) return ERROR(corruption_detected);
                ip += headerSize;
                FSEv05_buildDTable(DTableLL, norm, max, LLlog);
        }   }

        switch(Offtype)
        {
        case FSEv05_ENCODING_RLE :
            Offlog = 0;
            if (ip > iend-2) return ERROR(srcSize_wrong);   /* min : "raw", hence no header, but at least xxLog bits */
            FSEv05_buildDTable_rle(DTableOffb, *ip++ & MaxOff); /* if *ip > MaxOff, data is corrupted */
            break;
        case FSEv05_ENCODING_RAW :
            Offlog = Offbits;
            FSEv05_buildDTable_raw(DTableOffb, Offbits);
            break;
        case FSEv05_ENCODING_STATIC:
            if (!flagStaticTable) return ERROR(corruption_detected);
            break;
        case FSEv05_ENCODING_DYNAMIC :
        default :   /* impossible */
            {   unsigned max = MaxOff;
                headerSize = FSEv05_readNCount(norm, &max, &Offlog, ip, iend-ip);
                if (FSEv05_isError(headerSize)) return ERROR(GENERIC);
                if (Offlog > OffFSEv05Log) return ERROR(corruption_detected);
                ip += headerSize;
                FSEv05_buildDTable(DTableOffb, norm, max, Offlog);
        }   }

        switch(MLtype)
        {
        case FSEv05_ENCODING_RLE :
            MLlog = 0;
            if (ip > iend-2) return ERROR(srcSize_wrong); /* min : "raw", hence no header, but at least xxLog bits */
            FSEv05_buildDTable_rle(DTableML, *ip++);
            break;
        case FSEv05_ENCODING_RAW :
            MLlog = MLbits;
            FSEv05_buildDTable_raw(DTableML, MLbits);
            break;
        case FSEv05_ENCODING_STATIC:
            if (!flagStaticTable) return ERROR(corruption_detected);
            break;
        case FSEv05_ENCODING_DYNAMIC :
        default :   /* impossible */
            {   unsigned max = MaxML;
                headerSize = FSEv05_readNCount(norm, &max, &MLlog, ip, iend-ip);
                if (FSEv05_isError(headerSize)) return ERROR(GENERIC);
                if (MLlog > MLFSEv05Log) return ERROR(corruption_detected);
                ip += headerSize;
                FSEv05_buildDTable(DTableML, norm, max, MLlog);
    }   }   }

    return ip-istart;
}